#pragma once

#include "ProgressionManager.h"

#include "SDLUtils.h"
#include "Texture.h"

#include <memory>

class ScenesManager;
class RNG_Manager;
class MainMenuScene;
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
    std::shared_ptr<MainMenuScene> _mainMenuScene;

private:
    Texture* _t;

    #ifdef _DEBUG
        void restart();
        bool _restartRequested = false;
    #endif
};