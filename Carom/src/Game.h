#pragma once

class ScenesManager;
class B2Manager;

class Game {
public:
    Game();
    virtual ~Game();

    void init();
    void start();

protected:
    ScenesManager* _sceneManager;
    B2Manager* _b2World;
};