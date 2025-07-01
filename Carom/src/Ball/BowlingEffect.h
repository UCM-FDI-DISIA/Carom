#pragma once
#include "BallEffect.h"

class BowlingEffect : public BallEffect
{
private:
    static constexpr float DENSITY = 1.5f;
    static constexpr float FRICTION = 0.4f;
    float _mult;
public:
    BowlingEffect(BallHandler* hndlr) : BallEffect(hndlr) {
        _name = "Pesado";
        _description = "La bola es un 50% más pesada";
        updateEffect();
    }
    ~BowlingEffect() {}

    void updateEffect();
    void onMultChanged() override;

    __EFFID_DECL__(effect::BOWLING);
    effectId_t getEffectId() override {return effect::BOWLING; };
};