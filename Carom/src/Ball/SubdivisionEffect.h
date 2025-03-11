#pragma once

#include "BallEffect.h"

namespace ecs{
    class SubdivisionEffect : public BallEffect{
        ecs::entity_t _target;
    public:
    __CMPID_DECL__(ecs::cmp::SUBDIVISION_EFFECT)

        SubdivisionEffect(ecs::entity_t ent, ecs::entity_t target) : BallEffect(ent), _target(target) {}
        ~SubdivisionEffect() {}

        void onStrikeEnd() override;
    };
}