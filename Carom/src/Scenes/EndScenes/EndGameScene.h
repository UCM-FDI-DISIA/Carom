#pragma once
#include "UIScene.h"
#include "MainMenuScene.h"

#include <memory>

class ScenesManager;
class GameScene;

class EndGameScene: public UIScene {  
public:
    EndGameScene(Game* g); // para cuando se pierde.
    virtual ~EndGameScene() = default;
};