#pragma once
#include "BallEffect.h"

class QuanticEffect : public BallEffect
{
private:
    bool _wasHit = false;
public:
    void onHit(ecs::entity_t ent) override;
    void onStrikeEnd() override;
    __CMPID_DECL__(ecs::cmp::QUANTIC_EFFECT)
};