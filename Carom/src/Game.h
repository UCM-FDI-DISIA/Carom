#pragma once

#include "ProgressionManager.h"

#include "SDL_video.h"
#include "SDLUtils.h"
#include "Texture.h"

class ScenesManager;
class ProgressionManager;

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
    inline ProgressionManager* getProgressionManager() {return _progressionManager;}
    
protected:
    ScenesManager* _sceneManager;
    ProgressionManager* _progressionManager;

private:
    Texture* _t;

    #ifdef _DEBUG
        void restart();
        bool _restartRequested = false;
    #endif
};