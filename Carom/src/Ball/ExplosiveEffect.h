#pragma once

#include "BallEffect.h"
#include <box2d/box2d.h>


namespace ecs {
    class ExplosiveEffect : public BallEffect {
        float _explosionDelay, _explosionStart, _radius, _force;
        bool _exploded;
        b2ShapeId _id;
        void createExplosion();
    public:

        __CMPID_DECL__(cmp::EXPLOSIVE_EFFECT);
        ecs::cmpId_t getEffectId() {return ecs::cmp::EXPLOSIVE_EFFECT;};

        ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force);
        ~ExplosiveEffect();

        void init() override;
        void update() override;

        void onHit(ecs::entity_t ent) {}
        void onStrikeEnd() override {}
        void onBeingTargeted() override {}
    };
}