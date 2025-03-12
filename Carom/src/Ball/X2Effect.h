#pragma once
#include "BallEffect.h"

class X2Effect : BallEffect
{
public:
    X2Effect(ecs::entity_t ent) : BallEffect(ent) {
        _name = "X2";
        _description = "Todos los otros efectos de esta bola que contengan números afectan el doble";
    }
    ~X2Effect() {}
    void init() override;

    __CMPID_DECL__(ecs::cmp::X2_EFFECT);
};