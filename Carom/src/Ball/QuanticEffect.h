#pragma once
#include "BallEffect.h"
#include "BallHandler.h"

class QuanticEffect : public BallEffect
{
private:
    bool _wasHit = false;
public:
    QuanticEffect(entity_t ent) : BallEffect(ent){
        _name = "Cuántica";
        _description = "X2 puntos al final del tiro si no es golpeada";
    }
    ~QuanticEffect() {}

    void init() override;
    void onHit(entity_t ent) override;
    void onStrikeEnd() override;
    __CMPID_DECL__(cmp::QUANTIC_EFFECT)
    cmpId_t getEffectId() {return cmp::QUANTIC_EFFECT;};
};