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
        void createBulletHole(const b2Vec2& pos);  
        void createBulletHoles(int n);  

        bool canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius);
    };
}
