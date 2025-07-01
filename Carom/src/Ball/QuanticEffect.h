#pragma once
#include "BallEffect.h"

class QuanticEffect : public BallEffect
{
private:
    bool _wasHit = false;
public:
    QuanticEffect(BallHandler* hndlr) : BallEffect(hndlr){
        _name = "Cuántica";
        _description = "X2 puntos al final del tiro si no es golpeada";
    }
    ~QuanticEffect() {}

    void init() override;
    void onHit(entity_t ent) override;
    void onStrikeEnd() override;
   
    __EFFID_DECL__(effect::QUANTIC);
    effectId_t getEffectId() override {return effect::QUANTIC;};
};