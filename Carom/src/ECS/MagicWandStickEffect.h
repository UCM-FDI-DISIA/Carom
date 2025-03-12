#pragma once

#include "StickEffectComponent.h"

namespace ecs{
class MagicWandStickEffect : public StickEffectComponent{
    MagicWandStickEffect(entity_t ent) : StickEffectComponent(ent) {}
    ~MagicWandStickEffect() {}

    virtual void applyEffect(entity_t ent) override;
};
}