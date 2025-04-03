#pragma once
#include "UIScene.h"

class ScenesManager;
class RewardScene: public UIScene {
public:
    RewardScene(Game* g); // para cuando se gana (hay reward).
    virtual ~RewardScene() = default;
    
private:
    entity_t createContinueButton(int x, int y,GameScene* scene);;
};
