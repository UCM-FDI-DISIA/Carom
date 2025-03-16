#define _FPS // ! comentar si quieres quitar el cout de FPS

#include "Game.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "GameScene.h"
#include "CaromScene.h"
#include "PoolScene.h"
#include "NullState.h"

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

void
Game::init() 
{
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

    // Gets refresh rate of monitor to set timestep
    _displayMode.refresh_rate = getMonitorRefreshRate(sdlutils().window());
    _timestep = 1000.0f/getMonitorRefreshRate(sdlutils().window());

    #ifdef _FPS
        std::cout << "Monitor refresh rate: " << _displayMode.refresh_rate <<std::endl;
        std::cout << "Current variable timestep: " << _timestep <<std::endl;
    #endif
}

// Used to adapt render fps for different refresh rates hardware
int Game::getMonitorRefreshRate(SDL_Window* window) 
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    if (displayIndex < 0) {
        std::cerr << "Failed to get display index" << std::endl;
        return -1;
    }

    // to get the current display mode
    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(displayIndex, &mode) != 0) {
        std::cerr << "Failed to get display mode" << std::endl;
        return -1;
    }

    // return the refresh rate in hz
    return mode.refresh_rate;
}

void
Game::start() 
{
    _sceneManager = new ScenesManager();    

    NullState* state = new NullState(nullptr);
    ecs::GameScene *ms = new ecs::PoolScene(state, this, nullptr);

    _sceneManager->pushScene(ms);
}

void Game::run()
{
    bool exit = false;
    
    sdlutils().showCursor();
	// reset the time before starting - so we calculate correct delta-time in the first iteration
	sdlutils().resetTime();
    
    // for debugging fps
    #if defined(_DEBUG) && defined(_FPS)
        int frameCount = 0;
        int time = 1000;
    #endif

    // Game loop capped by VSync (but has manual loop control for disabled functionality case)
    // Monitors with refresh higher than 120hz are capped to 120hz (120 is max)
    while(!exit) {
        // refresh the input handler
        Uint32 startTime = sdlutils().regCurrTime();

        ih().refresh();
        if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || ih().closeWindowEvent()) {
            exit = true;
            continue;
        }

        // So logic always runs at 120fps
        for (int i = 0; i < _timestep/PHYSICS_TIMESTEP; ++i){
            _sceneManager->handleEvent();
            _sceneManager->update();
        }

        if (ih().isWindowsFocused()) {
            sdlutils().clearRenderer();
            _sceneManager->render();
            sdlutils().presentRenderer();
        }

        #if defined(_DEBUG) && defined(_FPS)
            frameCount++;
            if (sdlutils().currRealTime() >= time){
                std::cout << "FPS: " << frameCount << std::endl;
                time = sdlutils().currRealTime() + 1000;
                frameCount = 0;
            }
        #endif

        Uint32 elapsed = sdlutils().currRealTime() - startTime;

        // SDL_Delay introduce errors for how it works under the hood. 
        // A way to deal with it is to call it with smaller durations.
        if (elapsed < _timestep) {
            Uint32 remainingTime = _timestep - elapsed;
            while(sdlutils().currRealTime() - startTime < _timestep) { // (elapsed < _timestep)
                if (remainingTime > 1)
                    SDL_Delay(remainingTime - 1);
                else
                    SDL_Delay(1); // Waiting for shorter periods increases precision
                remainingTime = _timestep - (sdlutils().currRealTime() - startTime);
            }
        }

    }

}
