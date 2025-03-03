#pragma once

class ScenesManager;

#include "SDL.h"
#include "Texture.h"

class Game {
public:
    static constexpr int nCushions = 4;

    static constexpr Uint32 FIXED_TIME_STEP = 1000/60;

    Game();
    virtual ~Game();

    void init();
    void start();

    inline auto getRenderer() const{
        return _t->getRenderer();
    }

    inline ScenesManager* getScenesManager() {return _sceneManager;}

protected:
    ScenesManager* _sceneManager;


private:
    Texture* _t;
};