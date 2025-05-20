#pragma once
#include "UIScene.h"
#include "Game.h"
#include "ItemIDs.h"
#include <memory>

class PauseScene: public UIScene {
    //escena sobre la que renderizar
    GameScene* _bottomScene;

    int previousTheme;

    void initObjects() override;

public:

    PauseScene(Game* game, GameScene* sceneToRenderOnTop);
    virtual ~PauseScene();

    void render() override;

    
};