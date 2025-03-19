#pragma once
#include "BallEffect.h"

namespace ecs{
class BowlingEffect : public BallEffect
{
private:
    static constexpr float DENSITY = 1.5f;
    static constexpr float FRICTION = 0.4f;
public:
    BowlingEffect(ecs::entity_t ent) : BallEffect(ent) {
        _name = "Pesado";
        _description = "La bola es un 50% más pesada";
    }
    ~BowlingEffect() {}

    void init() override;
    __CMPID_DECL__(ecs::cmp::BOWLING_EFFECT);
};}