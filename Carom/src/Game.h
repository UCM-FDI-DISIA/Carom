#pragma once

class ScenesManager; // TODO

class Game {
public:
    Game();
    virtual ~Game();

    void init();
    void start();

protected:
    ScenesManager* _sceneManager;
};