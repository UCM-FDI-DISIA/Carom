#pragma once

class ScenesManager;
class B2Manager;

class Game {
public:
    static constexpr int nCushions = 4;

    Game();
    virtual ~Game();

    void init();
    void start();

protected:
    ScenesManager* _sceneManager;
    B2Manager* _b2World;
};