#pragma once
#include "BallEffect.h"
class BallHandler;

class PetanqueEffect : public BallEffect
{
private:
    const float MAX_DISTANCE = 50;
public:
    PetanqueEffect(entity_t ent) : BallEffect(ent) {
        _name = "Petanca";
        _description = "Cuanto más cerca esté de la bola blanca al final de la partida más se multiplicará la puntuación final";
    }
    ~PetanqueEffect() {}

    void init() override;
    void onStrikeEnd() override;
    __CMPID_DECL__(cmp::PETANQUE_EFFECT);
    cmpId_t getEffectId() override {return cmp::PETANQUE_EFFECT; };
};