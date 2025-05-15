// #define _FPS // ! comentar si quieres quitar el cout de FPS

#include <unordered_map>
#include <utility>

#include "Game.h"
#include "InputHandler.h"
#include "InventoryManager.h"

#include "ScenesManager.h"
#include "GameScene.h"
#include "CaromScene.h"
#include "PoolScene.h"
#include "MainMenuScene.h"
#include "NullState.h"

#include "CaromScene.h"
#include "CowboyPoolScene.h" // ! tst
#include "AudioManager.h"
#include "QuitScene.h"

#include "QuitScene.h"

#include <memory>

Game::Game() : _exit(false), _paused(false) {}

Game::~Game() 
{
    delete _sceneManager; // HAS TO BE FIRST
    delete _progressionManager;
    _mainMenuScene.reset();

    if (RNG_Manager::HasInstance())
        RNG_Manager::Release();

    if (InventoryManager::HasInstance())
        InventoryManager::Release();

    // release InputHandler if the instance was created correctly.
    if (InputHandler::HasInstance())
        InputHandler::Release();

    if (AudioManager::HasInstance())
        AudioManager::Release();

    // release SLDUtil if the instance was created correctly.
    if (SDLUtils::HasInstance())
        SDLUtils::Release();

}

void
Game::init() 
{
    // initialize SDL singleton
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

    // initialize InventoryManager singleton
    if(!InventoryManager::Init()) {
        std::cerr << "Something went wrong while initializing InventoryManager"
                << std::endl;
        return;
    }

    if(!AudioManager::Init()) {
        std::cerr << "Something went wrong while initializing Manager"
                << std::endl;
        return;
    }

    // initialize InventoryManager singleton
    if(!RNG_Manager::Init()) {
        std::cerr << "Something went wrong while initializing RNG_Manager"
                << std::endl;
        return;
    }
}

void
Game::start() 
{
    unsigned seed = RNG_Manager::Instance()->randomRange(1, 1000000); 
    RNG_Manager::Instance()->inseminate(seed);

    _progressionManager = new ProgressionManager();
    _progressionManager->setBossesList();

    _sceneManager = new ScenesManager();    
    _mainMenuScene = std::make_shared<MainMenuScene>(this);

    _sceneManager->pushScene(_mainMenuScene);
}

void Game::run()
{
    auto& ihdr = ih();
    auto& sdlut = sdlutils();
    //auto aMngr = new AudioManager();
    
    sdlut.showCursor();

    SDL_Surface *surface = IMG_Load("../../resources/images/cursor.png");
    SDL_Cursor *cursor = SDL_CreateColorCursor(surface, 33, 0);
    SDL_SetCursor(cursor);

	// reset the time before starting - so we calculate correct delta-time in the first iteration
	sdlutils().resetTime();
	sdlutils().virtualTimer().resetTime();
    
    // for debugging fps
    #if defined(_DEBUG) && defined(_FPS)
        int frameCount = 0;
        int time = 1000;
    #endif

    // Game loop capped by VSync (but has manual loop control for disabled functionality case)
    while(!_exit) {
        // store the current time -- all game objects should use this time when
		// they need to get the current time. They also have accesse to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().regCurrTime();
        sdlutils().virtualTimer().regCurrTime();
        
        // refresh the input handler
        ihdr.refresh();
        if ((ihdr.isKeyDown(SDL_SCANCODE_ESCAPE) || ihdr.closeWindowEvent()) && !_paused) {
            _sceneManager->pushScene(std::make_shared<QuitScene>(this, _sceneManager->top()));
            continue;
        }

        #if defined(_DEBUG)
        if (_restartRequested){
            restart();
            continue;
        }
        #endif

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

void 
Game::close() {
    _exit = true;
}

#ifdef _DEBUG
    void Game::restart()
    {
        _restartRequested = false;

        delete _sceneManager;
        _sceneManager = nullptr;

        _sceneManager = new ScenesManager();    

        std::shared_ptr<GameScene> ms = std::make_shared<GameScene>(this);
    
        _sceneManager->pushScene(ms);
    }
#endif
