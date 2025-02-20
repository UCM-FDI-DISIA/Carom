#include "Game.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "GameScene.h" // ! test
#include "CaromScene.h" // ! test
#include "PL_State.h" // ! test
#include "B2Manager.h" // ! test


Game::Game() {}

Game::~Game() {

    // release InputHandler if the instance was created correctly.
    if (InputHandler::HasInstance())
        InputHandler::Release();

    // release SLDUtil if the instance was created correctly.
    if (SDLUtils::HasInstance())
        SDLUtils::Release();

    // release B2Manager if the instance was created correctly.
    if (B2Manager::HasInstance())
        B2Manager::Release();
}

// TODO
void
Game::init() {
    // initialize SDL singleton
    // TODO: cargar los recursos correspondientes
	if (!SDLUtils::Init("Carom", 800, 600,
			"../../resources/config/test.resources.json")) {
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

    // Initialize B2Manager singleton
    if (!B2Manager::Init()) {
        std::cerr << "Something went wrong while initializing B2Manager"
                << std::endl;
        return;
    }

    _sceneManager = new ScenesManager();    
}

void
Game::start() {

    bool exit = false;

    auto &ihdlr = ih();

    PL_State *plst = new PL_State(nullptr); // ! tst 
    ecs::GameScene *ms = new CaromScene(plst, this, nullptr); // ! tst  
    _sceneManager->pushScene(ms); // ! tst

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
        
        sdlutils().clearRenderer();

        b2mngr().stepWorld(); 

        _sceneManager->handleEvent();
        _sceneManager->update();
        _sceneManager->render();

		sdlutils().presentRenderer();

    }

}