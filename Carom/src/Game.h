#pragma once

class ScenesManager;

#include "SDL.h"

class Game {
public:
    static constexpr int nCushions = 4;

    static constexpr Uint32 FIXED_TIME_STEP = 1000/60;

    Game();
    virtual ~Game();

    void init();
    void start();

protected:
    ScenesManager* _sceneManager;
};