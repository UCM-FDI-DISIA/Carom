#pragma once
#include "EndScene.h"
namespace ecs{
    class ScenesManager;
    class RewardScene: public EndScene {
    public:
        RewardScene(Game* g); // para cuando se gana (hay reward).
        virtual ~RewardScene() = default;
    };
}