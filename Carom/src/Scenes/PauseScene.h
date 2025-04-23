#pragma once
#include "GameScene.h"
#include "Game.h"

class PauseScene: public GameScene{
    //escena sobre la que renderizar
    GameScene* _bottomScene = nullptr;

    void instantiateInventory();
    void createBallInfo();
    void showBall(int i);
    void hideBall(int i);
public:

    PauseScene(Game* game, GameScene* sceneToRenderOnTop);

    void render() override;
};