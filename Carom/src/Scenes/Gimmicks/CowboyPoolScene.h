#pragma once

#include "CaromScene.h"

namespace ecs{

    class CowboyPoolScene : public ecs::CaromScene {
        void initGimmick();
        void applyBossModifiers() override;
        void clearBossModifiers() override;

        void animateBossHand();

        // Gimmicks
        void createSandBank();
        void createBulletHole();

    public:
        CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss);
            
    };
}
