// #define _FPS // ! comentar si quieres quitar el cout de FPS

#include <unordered_map>
#include <utility>

#include "Game.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "GameScene.h"
#include "CaromScene.h"
#include "PoolScene.h"
#include "NullState.h"

#include "CaromScene.h"
#include "PrefabTestScene.h"
#include "CowboyPoolScene.h" // ! tst


Game::Game() {}

Game::~Game() {

    // release InputHandler if the instance was created correctly.
    if (InputHandler::HasInstance())
        InputHandler::Release();

    // release SLDUtil if the instance was created correctly.
    if (SDLUtils::HasInstance())
        SDLUtils::Release();

    delete _sceneManager;
}

void
Game::init() 
{
    // initialize SDL singleton
    // TODO: cargar los recursos correspondientes
	if (!SDLUtils::Init("Carom", 1920, 1080, "../../resources/config/resources.json")) {
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

    // Gets refresh rate of monitor to set timestep
    _displayMode.refresh_rate = getMonitorRefreshRate(sdlutils().window());
    _timestep = 1000.0f/getMonitorRefreshRate(sdlutils().window()) - 1; // the "-1ms" is to benefit the VSync
    // _logicTimestep = 

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
    // ecs::GameScene *ms = new ecs::CaromScene(state, this, nullptr); // ! tst  
    //ecs::GameScene *ms = new PrefabTestScene(state, this, nullptr); //no borrar, pruebas jordi
    ecs::GameScene *ms = new ecs::PoolScene(state, this, nullptr); 
    _sceneManager->pushScene(ms); // ! tst
}

void Game::run()
{
    bool exit = false;

    auto& ihdr = ih();
    auto& sdlut = sdlutils();
    
    sdlut.showCursor();
	// reset the time before starting - so we calculate correct delta-time in the first iteration
	sdlutils().resetTime();
	sdlutils().virtualTimer().resetTime();
    
    // for debugging fps
    #if defined(_DEBUG) && defined(_FPS)
        int frameCount = 0;
        int time = 1000;
    #endif

    // Game loop capped by VSync (but has manual loop control for disabled functionality case)
    // Monitors with refresh higher than 120hz are capped to 120hz (120 is max)
    while(!exit) {
        // store the current time -- all game objects should use this time when
		// they need to get the current time. They also have accesse to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();
        sdlutils().virtualTimer().regCurrTime();
		// refresh the input handler
		ihdr.refresh();

		if (ihdr.isKeyDown(SDL_SCANCODE_ESCAPE) || ihdr.closeWindowEvent()) {
			exit = true;
			continue;
		}
        
        Uint32 startTime = sdlut.regCurrTime();
        
        // refresh the input handler
        ihdr.refresh();
        if (ihdr.isKeyDown(SDL_SCANCODE_ESCAPE) || ihdr.closeWindowEvent()) {
            exit = true;
            continue;
        }

        if (_restartRequested){
            restart();
            continue;
        }

        // So logic always runs at 120fps
        for (int i = 0; i < _timestep/PHYSICS_TIMESTEP; ++i){
            _sceneManager->handleEvent();
            _sceneManager->update();
        }

        if (ihdr.isWindowsFocused()) {
            sdlut.clearRenderer();
            _sceneManager->render();
            sdlut.presentRenderer();
        }

        _sceneManager->refresh();

        #if defined(_DEBUG) && defined(_FPS)
            frameCount++;
            if (sdlutils().currRealTime() >= time){
                std::cout << "FPS: " << frameCount << std::endl;
                time = sdlutils().currRealTime() + 1000;
                frameCount = 0;
            }
        #endif

        Uint32 elapsed = sdlut.currRealTime() - startTime;

        // SDL_Delay introduce errors for how it works under the hood. 
        // A way to deal with it is to call it with smaller durations.
        if (elapsed < _timestep) {
            Uint32 remainingTime = _timestep - elapsed;
            while(sdlut.currRealTime() - startTime < _timestep) { // (elapsed < _timestep)
                if (remainingTime > 1)
                    SDL_Delay(remainingTime - 1);
                else
                    SDL_Delay(1); // Waiting for shorter periods increases precision
                remainingTime = _timestep - (sdlut.currRealTime() - startTime);
            }
        }

    }

}

#ifdef _DEBUG
    void Game::restart()
    {
        _restartRequested = false;

        delete _sceneManager;
        _sceneManager = nullptr;

        _sceneManager = new ScenesManager();    

        NullState* state = new NullState(nullptr);
        ecs::GameScene *ms = new ecs::CowboyPoolScene(state, this, nullptr, true);
    
        _sceneManager->pushScene(ms);
    }
#endif
