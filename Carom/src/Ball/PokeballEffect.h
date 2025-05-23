#pragma once
#include "BallEffect.h"
class BallHandler;

class PokeballEffect : public BallEffect
{
private:
public:
    PokeballEffect(entity_t ent) : BallEffect(ent){
        _name = "Pokeball";
        _description = "Absorbe todos los efectos de la primera bola con la que colisione";
    }
    ~PokeballEffect() {}

    void onHit(entity_t ent) override;

    __CMPID_DECL__(cmp::POKEBALL_EFFECT);
    cmpId_t getEffectId() override {return cmp::POKEBALL_EFFECT; };
};