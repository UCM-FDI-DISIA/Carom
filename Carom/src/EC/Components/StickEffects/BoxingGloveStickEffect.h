#pragma once

#include "StickEffectComponent.h"

class Inventory;

class BoxingGloveStickEffect : public StickEffectComponent {
private:
friend Inventory;
    const float FRICTION_FACTOR = 0.75f;
public:
    __CMPID_DECL__(cmp::BOXING_GLOVE_STICK);

    BoxingGloveStickEffect(entity_t entity);
    ~BoxingGloveStickEffect();
    void applyEffect(entity_t target) override;
};
