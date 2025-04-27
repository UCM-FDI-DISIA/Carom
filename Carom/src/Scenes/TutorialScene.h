#pragma once
#include "GameScene.h"
#include "Game.h"

class TutorialScene: public GameScene{
    //escena sobre la que renderizar
    GameScene* _bottomScene = nullptr;
public:

    TutorialScene(Game* game, GameScene* sceneToRenderOnTop);

    void render() override;
};