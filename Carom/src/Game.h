#pragma once

class ScenesManager;

#include "SDL_video.h"
#include "SDLUtils.h"
#include "Texture.h"

class Game {
public:

    static constexpr float PHYSICS_TIMESTEP = 1000.0f/120.0f;

    Game();
    virtual ~Game();

    void init();
    void start();
    void run();
    
    inline auto getRenderer() const{
        return _t->getRenderer();
    }
    inline int getDisplayRefresh() const { return _displayMode.refresh_rate; }
    
    inline ScenesManager* getScenesManager() {return _sceneManager;}
    
protected:
    ScenesManager* _sceneManager;
    
    int getMonitorRefreshRate(SDL_Window *window);

private:
    Texture* _t;

    Uint32 _timestep; // variable frame duration
    SDL_DisplayMode _displayMode; // to get the monitos
};