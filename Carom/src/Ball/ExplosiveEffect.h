#pragma once

#include "BallEffect.h"
#include <box2d>


namespace ecs {
    class ExplosiveEffect : public BallEffect {
        float _explosionDelay, _explosionStart, _radius;

        bool _exploted;

        b2ShapeId _id;
        public:
        ExplosiveEffect(entity_t ent, float timeForExplosion, float radius);
        ~ExplosiveEffect();

        void init() override;
        void update() override;

        void onHit(ecs::entity_t ent) {}
        void onStrikeEnd() override {}
        void onBeingTargeted() override {}
    };
}