#pragma once
#include "BallEffect.h"
class BallHandler;

class PokeballEffect : public BallEffect
{
private:
public:
    PokeballEffect(ecs::entity_t ent) : BallEffect(ent){
        _name = "Pokeball";
        _description = "Absorbe todos los efectos de la primera bola con la que colisione";
    }
    ~PokeballEffect() {}

    void onHit(ecs::entity_t ent) override;

    __CMPID_DECL__(ecs::cmp::POKEBALL_EFFECT);
};