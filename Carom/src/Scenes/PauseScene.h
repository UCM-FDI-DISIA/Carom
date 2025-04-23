#pragma once
#include "GameScene.h"
#include "Game.h"

#include <memory>

class PauseScene: public GameScene{
    //escena sobre la que renderizar
    GameScene* _bottomScene;

    void instantiateInventory();
public:

    PauseScene(Game* game, GameScene* sceneToRenderOnTop);

    void render() override;
};