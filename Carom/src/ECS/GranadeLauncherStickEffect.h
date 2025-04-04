#pragma once 

#include "StickEffectComponent.h"


class GranadeLauncherStickEffect : public StickEffectComponent {
    float _explosionForce, _explosionDelay, _radius;
public:
    __CMPID_DECL__(cmp::GRANADE_LAUCHER_STICK);

    GranadeLauncherStickEffect(entity_t ent, float radius, float explosionForce, float explosionDelay);
    ~GranadeLauncherStickEffect();

    void init() override;
    void applyEffect(entity_t ball) override;
};
