#pragma once
#include "GameScene.h"
#include "Game.h"

class HelperScene: public GameScene{
    //escena sobre la que aparecer
    GameScene* _bottomScene = nullptr;
public:

    HelperScene(Game* game, GameScene* sceneToRenderOnTop);

    void render() override;
    void update() override;
    void handleEvent() override;
};