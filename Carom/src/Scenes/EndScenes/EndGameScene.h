#pragma once
#include "UIScene.h"
#include "MainMenuScene.h"

#include <memory>

class ScenesManager;
class GameScene;

class EndGameScene: public UIScene {  
public:
    EndGameScene(Game* g, bool win);
    virtual ~EndGameScene() = default;

protected:
    void initObjects() override;

    void hasWon();
    void hasLost();

    bool _win; // variable con la cual se inicializa EndScene
};