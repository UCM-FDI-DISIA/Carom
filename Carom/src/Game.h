#pragma once

class ScenesManager;

#include "SDL_video.h"
#include "SDLUtils.h"
#include "Texture.h"

class ScenesManager;
class RNG_Manager;
class MainMenuScene;

class Game {
public:

    static constexpr float FIXED_TIMESTEP = 1000.0f/60.0f;

    Game();
    virtual ~Game();

    void init();
    void start();
    void run();

    #ifdef _DEBUG
        inline void requestRestart() { _restartRequested = true; }
    #endif
    
    inline auto getRenderer() const{
        return _t->getRenderer();
    }
    
    inline ScenesManager* getScenesManager() {return _sceneManager;}
    inline RNG_Manager& getRGN() { return *_rngManager; };
    
protected:
    ScenesManager* _sceneManager;
    MainMenuScene* _mainMenuScene;
    RNG_Manager* _rngManager;

private:
    Texture* _t;

    #ifdef _DEBUG
        void restart();
        bool _restartRequested = false;
    #endif
};