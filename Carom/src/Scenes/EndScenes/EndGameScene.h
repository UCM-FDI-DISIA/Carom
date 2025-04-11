#pragma once
#include "UIScene.h"
#include "MainMenuScene.h"

class ScenesManager;
class GameScene;

class EndGameScene: public UIScene {  
public:
    EndGameScene(Game* g); // para cuando se pierde.
    virtual ~EndGameScene() = default;

private:
    entity_t createExitButton(int x, int y, GameScene* scene);
    entity_t createSVGExitButton(std::string tag, std::string image, GameScene *scene);
};