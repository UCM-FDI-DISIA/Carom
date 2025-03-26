#pragma once
#include "EndScene.h"
class ScenesManager;
class RewardScene: public EndScene {
public:
    RewardScene(Game* g); // para cuando se gana (hay reward).
    virtual ~RewardScene() = default;
};