#pragma once
#include "UIScene.h"

class ScenesManager;
class Reward;

class RewardScene: public UIScene {
public:
    RewardScene(Game* g, std::shared_ptr<Reward> r); // para cuando se gana (hay reward).
    virtual ~RewardScene() = default;
};
