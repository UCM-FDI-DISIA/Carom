#pragma once
#include "BallEffect.h"
class BallHandler;

class PokeballEffect : public BallEffect
{
private:
    BallHandler* _handler;
public:
    PokeballEffect(ecs::entity_t ent) : BallEffect(ent) {}
    ~PokeballEffect() {}

    void onHit(ecs::entity_t ent) override;

    __CMPID_DECL__(ecs::cmp::POKEBALL_EFFECT);
};