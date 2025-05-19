#pragma once

#include "StickEffectComponent.h"


class MagicWandStickEffect : public StickEffectComponent{
public:
    __CMPID_DECL__(cmp::MAGIC_WAND_STICK);

    MagicWandStickEffect(entity_t ent) : StickEffectComponent(ent) {}
    ~MagicWandStickEffect() {}
    void applyEffect(entity_t target) override;
};
