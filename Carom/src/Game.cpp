#include "Game.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "ScenesManager.h"

Game::Game() {}

Game::~Game() {}

// TODO
void
Game::init() {
    // initialize SDL singleton
	if (!SDLUtils::Init("Ping Pong", 800, 600,
			"resources/config/test.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}

	// initialize InputHandler singleton
    if (!InputHandler::Init()) {
        std::cerr << "Something went wrong while initializing SDLHandler"
                << std::endl;
        return;
    }

    _sceneManager = new ScenesManager();
}

void
Game::start() {

    bool exit = false;

    // recoger input

    while(!exit) {
        _sceneManager->handleEvent();
        _sceneManager->update();
        _sceneManager->render();
    }

}