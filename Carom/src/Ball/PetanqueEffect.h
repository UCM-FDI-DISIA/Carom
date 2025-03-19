#pragma once
#include "BallEffect.h"

class PetanqueEffect : BallEffect
{
public:
    PetanqueEffect(ecs::entity_t ent) : BallEffect(ent) {
        _name = "Petanca";
        _description = "Cuanto más cerca esté de la bola blanca al final de la partida más se multiplicará la puntuación final";
    }
    ~PetanqueEffect() {}

    void onStrikeEnd() override;
    __CMPID_DECL__(ecs::cmp::PETANQUE_EFFECT);
};