#pragma once
#include "GameScene.h"
#include "Game.h"

class PauseScene: public GameScene{
    //escena sobre la que renderizar
    GameScene* _bottomScene = nullptr;
public:

    PauseScene(Game* game, GameScene* sceneToRenderOnTop);

    void render() override;
};