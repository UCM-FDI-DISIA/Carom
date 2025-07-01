#pragma once
#include "BallEffect.h"

class PokeballEffect : public BallEffect
{
private:
public:
    PokeballEffect(BallHandler* hndlr) : BallEffect(hndlr){
        _name = "Pokeball";
        _description = "Absorbe todos los efectos de la primera bola con la que colisione";
    }
    ~PokeballEffect() {}

    void onHit(entity_t ent) override;

    __EFFID_DECL__(effect::POKEBALL);
    effectId_t getEffectId() override {return effect::POKEBALL; };
};