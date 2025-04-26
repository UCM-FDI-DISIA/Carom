#pragma once

#include "BallEffect.h"
#include <box2d/box2d.h>


class RigidBodyComponent;
class ExplosiveEffect : public BallEffect {
    float _explosionDelay, _explosionStart, _radius, _force;
    bool _exploded;
    RigidBodyComponent* _myRigidbody;

    void createExplosion();
public:

    __CMPID_DECL__(cmp::EXPLOSIVE_EFFECT);
    cmpId_t getEffectId() override {return cmp::EXPLOSIVE_EFFECT;}

    ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force);
    ~ExplosiveEffect();

    void init() override;
    void update() override;

    void onHit(entity_t ent) {}
    void onStrikeEnd() override {}
    void onBeingTargeted() override {}
};
