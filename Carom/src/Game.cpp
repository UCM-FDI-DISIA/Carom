#include "Game.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "GameScene.h" // ! test
#include "CaromScene.h" // ! test
#include "PL_State.h" // ! test


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
	if (!SDLUtils::Init("Carom", 1920, 1080, "../../resources/config/test.resources.json", "../../resources/svg/Game.svg")) {
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

    auto &ihdlr = ih();

    PL_State *plst = new PL_State(nullptr); // ! tst 
    ecs::GameScene *ms = new ecs::CaromScene(plst, this, nullptr); // ! tst  
    _sceneManager->pushScene(ms); // ! tst

	// reset the time before starting - so we calculate correct delta-time in the first iteration
	sdlutils().resetTime();

    while(!exit) {
        // store the current time -- all game objects should use this time when
		// they need to get the current time. They also have accesse to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
        
        sdlutils().clearRenderer();

        _sceneManager->handleEvent();
        _sceneManager->update();
        _sceneManager->render();

		sdlutils().presentRenderer();

        Uint32 elapsed = startTime - sdlutils().currRealTime();

        // Forzado a que el juego no vaya mas rápido que 60 fps
        if (elapsed < FIXED_TIME_STEP)
			SDL_Delay(FIXED_TIME_STEP - elapsed);
    }

}