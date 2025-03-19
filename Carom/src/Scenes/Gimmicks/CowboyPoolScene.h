#pragma once

#include "CaromScene.h"

namespace ecs{

    class CowboyPoolScene : public ecs::CaromScene {
    public:
            CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss);

    protected:
        void initGimmick();
        void applyBossModifiers() override;
        void clearBossModifiers() override;

        void animateBossHand();

        // Gimmicks
        void createSandBank();

        // Boss modifiers
        entity_t createBulletHole(const b2Vec2& pos);  
        void createBulletHoles(int n);  
    };
}
