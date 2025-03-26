#include "Game.h"

#include "SDLUtils.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "GameScene.h" // ! test
#include "CaromScene.h" // ! test
#include "PoolScene.h"
#include "NullState.h" // ! test A

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
	if (!SDLUtils::Init("Carom", 1920, 1080, 
            "../../resources/config/resources.json", 
            "../../resources/svg/Game.svg", 
            "../../resources/svg/positions.svg"
        )) {
		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}
    auto utils = SDLUtils::Instance();
    utils->toggleFullScreen();

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
    
    sdlutils().showCursor();

    NullState* state = new NullState(nullptr);
    //GameScene *ms = new CaromScene(state, this, nullptr); // ! tst  
    GameScene *ms = new PoolScene(state, this, nullptr);
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

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE) || ihdlr.closeWindowEvent()) {
			exit = true;
			continue;
		}
        
        sdlutils().clearRenderer();

        _sceneManager->handleEvent();
        _sceneManager->update();

        if (ihdlr.isWindowsFocused()) {
            _sceneManager->render();
            sdlutils().presentRenderer();
            sdlutils().clearRenderer();
        }

        Uint32 elapsed = startTime - sdlutils().currRealTime();

        // Forzado a que el juego no vaya mas rápido que 60 fps
        if (elapsed < FIXED_TIME_STEP)
			SDL_Delay(FIXED_TIME_STEP - elapsed);
    }

}