#include "Game.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "CaromScene.h"

Game::Game() {}

Game::~Game() {

    // release InputHandler if the instance was created correctly.
    if (InputHandler::HasInstance())
        InputHandler::Release();

    // release SLDUtil if the instance was created correctly.
    if (SDLUtils::HasInstance())
        SDLUtils::Release();
}

// TODO
void
Game::init() {
    // initialize SDL singleton
    // TODO: cargar los recursos correspondientes
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
    CaromScene* c = new CaromScene(this, nullptr);
    _sceneManager->pushScene(c);
}

void
Game::start() {

    bool exit = false;

    auto &ihdlr = ih();

	// reset the time before starting - so we calculate correct delta-time in the first iteration
	sdlutils().resetTime();

    while(!exit) {
        // store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

        _sceneManager->handleEvent();
        _sceneManager->update();
        _sceneManager->render();
    }

}