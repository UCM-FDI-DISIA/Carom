#pragma once
#include "BallEffect.h"

namespace ecs{
class QuanticEffect : public BallEffect
{
private:
    bool _wasHit = false;
public:
    QuanticEffect(ecs::entity_t ent) : BallEffect(ent) {}
    ~QuanticEffect() {}

    void onHit(ecs::entity_t ent) override;
    void onStrikeEnd() override;
    __CMPID_DECL__(ecs::cmp::QUANTIC_EFFECT)
};
}