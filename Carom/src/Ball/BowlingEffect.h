#pragma once
#include "BallEffect.h"

class BowlingEffect : public BallEffect
{
private:
    static constexpr float DENSITY = 1.5f;
    static constexpr float FRICTION = 0.4f;
    float _mult;
public:
    BowlingEffect(entity_t ent) : BallEffect(ent) {
        _name = "Pesado";
        _description = "La bola es un 50% más pesada";
    }
    ~BowlingEffect() {}

    void init() override;
    void updateEffect();
    void onMultChanged() override;
    __CMPID_DECL__(cmp::BOWLING_EFFECT);

    cmpId_t getEffectId() override {return cmp::BOWLING_EFFECT; };
};