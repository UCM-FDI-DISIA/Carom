#pragma once
#include "BallEffect.h"
class BallHandler;

class PokeballEffect : public BallEffect
{
private:
    BallHandler* _handler;
public:
    void onHit(ecs::entity_t ent) override;
    void init() override;

    __CMPID_DECL__(ecs::cmp::POKEBALL_EFFECT);
};