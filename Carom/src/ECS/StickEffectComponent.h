#pragma once

#include "Component.h"


class StickEffectComponent : public Component {
public:
    StickEffectComponent(entity_t entity) : Component(entity) {}
    virtual ~StickEffectComponent() {}

    virtual void applyEffect(entity_t target) = 0;

    void update() override {}
    void handleEvent() override {}
    void render() override {}
};
