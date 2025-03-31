#define _FPS // ! comentar si quieres quitar el cout de FPS

#include <unordered_map>
#include <utility>

#include "Game.h"
#include "InputHandler.h"

#include "ScenesManager.h"
#include "GameScene.h"
#include "CaromScene.h"
#include "PoolScene.h"
#include "MainMenuScene.h"
#include "NullState.h"

#include "CaromScene.h"
#include "PrefabTestScene.h"
#include "CowboyPoolScene.h" // ! tst


Game::Game() {}

Game::~Game() {

    delete _sceneManager; // HAS TO BE FIRST

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
}

void
Game::start() 
{
    _sceneManager = new ScenesManager();    

    NullState* state = new NullState(nullptr);
    // ecs::GameScene *ms = new ecs::CaromScene(state, this, nullptr); // ! tst  
    ecs::GameScene *ms = new ecs::PoolScene(this); //no borrar, pruebas jordi
    //ecs::GameScene *ms = new ecs::PoolScene(state, this, nullptr); 
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

        if (_restartRequested){
            restart();
            continue;
        }

        _sceneManager->handleEvent();
        _sceneManager->update();
        _sceneManager->refresh();

        if (ihdr.isWindowsFocused()) {
            sdlut.clearRenderer();
            _sceneManager->render();
            sdlut.presentRenderer();
        }


        #if defined(_DEBUG) && defined(_FPS)
            frameCount++;
            if (sdlutils().currRealTime() >= time){
                std::cout << "FPS: " << frameCount << std::endl;
                time = sdlutils().currRealTime() + 1000;
                frameCount = 0;
            }
        #endif

        Uint32 elapsed = sdlut.currRealTime() - startTime;

        if (elapsed < FIXED_TIMESTEP) {
                SDL_Delay(FIXED_TIMESTEP - elapsed);
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
        ecs::GameScene *ms = new ecs::PoolScene(this);
    
        _sceneManager->pushScene(ms);
    }
#endif
