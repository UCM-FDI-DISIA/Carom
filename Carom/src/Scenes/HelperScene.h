#pragma once
#include "GameScene.h"
#include "Game.h"

class HelperScene: public GameScene{
    //escena sobre la que aparecer
    std::shared_ptr<GameScene> _bottomScene = nullptr;
public:

    HelperScene(Game* game, std::shared_ptr<GameScene> sceneToRenderOnTop);

    void render() override;
    void update() override;
    void handleEvent() override;
};