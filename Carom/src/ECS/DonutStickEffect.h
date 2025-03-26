#pragma once

#include "StickEffectComponent.h"
class DonutStickEffect : public StickEffectComponent {
private:
    float _factor;
public:
    __CMPID_DECL__(cmp::BOXING_GLOVE_STICK);

    DonutStickEffect(entity_t entity) : StickEffectComponent(entity) {}
    ~DonutStickEffect() {}
    void applyEffect(entity_t target) override;
};