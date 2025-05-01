#pragma once
#include "UIScene.h"

#include <memory>

class ScenesManager;
class RewardScene: public UIScene {
public:
    RewardScene(Game* g); // para cuando se gana (hay reward).
    virtual ~RewardScene() = default;
};
