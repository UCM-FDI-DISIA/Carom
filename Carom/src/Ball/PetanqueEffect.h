#pragma once
#include "BallEffect.h"

class PetanqueEffect : public BallEffect
{
private:
    const float MAX_DISTANCE = 2;
public:
    PetanqueEffect(BallHandler* hndlr) : BallEffect(hndlr) {
        _name = "Petanca";
        _description = "Cuanto más cerca esté de la bola blanca al final de la partida más se multiplicará la puntuación final";
    }
    ~PetanqueEffect() {}

    void onStrikeEnd() override;

    __EFFID_DECL__(effect::ABBACUS);
    effectId_t getEffectId() override {return effect::PETANQUE; }
};