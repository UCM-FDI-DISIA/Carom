#pragma once


#include "SDL_video.h"
#include "SDLUtils.h"
#include "Texture.h"

#include <memory>
#include "ProgressionManager.h"

class AudioManager;
class ScenesManager;
class RNG_Manager;
class MainMenuScene;


class Game {
public:

    static constexpr float FIXED_TIMESTEP = 1000.0f/60.0f;

    static constexpr int BALL_ROLLING_ROWS = 1;
    static constexpr int BALL_ROLLING_COLS = 8;

    Game();
    virtual ~Game();

    void init();
    void start();
    void run();
    void close();

    inline void setPaused(bool state) { _paused = state; }

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
    std::shared_ptr<MainMenuScene> _mainMenuScene;
    ProgressionManager* _progressionManager;
    bool _exit; 
    bool _paused;

private:
    Texture* _t;

    #ifdef _DEBUG
        void restart();
        bool _restartRequested = false;
    #endif
};