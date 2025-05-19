#pragma once

#include "StickEffectComponent.h"

//! Doesn't work until physics bugs are solved

class DonutStickEffect : public StickEffectComponent {
private:
    float _factor;
public:
    __CMPID_DECL__(cmp::DONUT_STICK);

    DonutStickEffect(entity_t entity) : StickEffectComponent(entity) {}
    ~DonutStickEffect() {}
    void applyEffect(entity_t target) override;
};
