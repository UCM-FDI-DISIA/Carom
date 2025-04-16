#pragma once

#include "StickEffectComponent.h"

class BoxingGloveStickEffect : public StickEffectComponent {
private:
    float _factor;
public:
    __CMPID_DECL__(cmp::BOXING_GLOVE_STICK);

    BoxingGloveStickEffect(entity_t entity, float frictionFactor);
    ~BoxingGloveStickEffect();
    void applyEffect(entity_t target) override;
};
