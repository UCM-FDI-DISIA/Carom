#pragma once
#include "BallEffect.h"
#include "BallHandler.h"

class QuanticEffect : public BallEffect
{
private:
    bool _wasHit = false;
    BallHandler* _handler;
public:
    QuanticEffect(ecs::entity_t ent) : BallEffect(ent) {}
    ~QuanticEffect() {}

    void init() override;
    void onHit(ecs::entity_t ent) override;
    void onStrikeEnd() override;
    __CMPID_DECL__(ecs::cmp::QUANTIC_EFFECT)
};