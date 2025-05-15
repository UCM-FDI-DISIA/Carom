#pragma once
#include "UIScene.h"
#include "MainMenuScene.h"

#include <memory>

class ScenesManager;
class GameScene;

class EndGameScene: public UIScene {  
public:
    EndGameScene(Game* g, bool win, bool isBoss);
    virtual ~EndGameScene() = default;

protected:
    void initObjects() override;

    void hasWon();
    void standardWin();
    void bossWin();

    void hasLost();
    void standardLose();
    void bossLose();

    bool _win; // variable con la cual se inicializa EndScene
    bool _isBoss; // variable con la cual se inicializa EndScene
};