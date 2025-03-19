#pragma once
#include "BallEffect.h"
#include "BallHandler.h"

namespace ecs{
class QuanticEffect : public BallEffect
{
private:
    bool _wasHit = false;
    BallHandler* _handler;
public:
    QuanticEffect(ecs::entity_t ent) : BallEffect(ent){
        _name = "Cuántica";
        _description = "X2 puntos al final del tiro si no es golpeada";
    }
    ~QuanticEffect() {}

    void init() override;
    void onHit(ecs::entity_t ent) override;
    void onStrikeEnd() override;
    __CMPID_DECL__(ecs::cmp::QUANTIC_EFFECT)
};
}