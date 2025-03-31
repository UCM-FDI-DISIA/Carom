#pragma once

#include "BallEffect.h"
#include <iostream>

namespace ecs{
    class SubdivisionEffect : public BallEffect{
        entity_t _target;
    public:
        __CMPID_DECL__(cmp::SUBDIVISION_EFFECT)
        cmpId_t getEffectId() {return cmp::SUBDIVISION_EFFECT;};

        SubdivisionEffect(entity_t ent, entity_t target) : BallEffect(ent), _target(target) {}
        ~SubdivisionEffect() {}
        void onStrikeEnd() override;
    };
}