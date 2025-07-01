#pragma once
#include "BallEffect.h"

class X2Effect : public BallEffect
{
public:
    X2Effect(BallHandler* hndlr) : BallEffect(hndlr) {
        _name = "X2";
        _description = "Todos los otros efectos de esta bola que contengan números afectan el doble";
    }
    ~X2Effect() {}
    void init() override;

    __EFFID_DECL__(effect::X2);
    effectId_t getEffectId() override {return effect::X2;};
};