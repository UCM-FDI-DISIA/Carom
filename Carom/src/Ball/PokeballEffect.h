#pragma once
#include "BallEffect.h"
namespace ecs{
class BallHandler;}

namespace ecs{
class PokeballEffect : public BallEffect
{
private:
    BallHandler* _handler;
public:
    PokeballEffect(ecs::entity_t ent) : BallEffect(ent) {}
    ~PokeballEffect() {}

    void onHit(ecs::entity_t ent) override;
    void init() override;

    __CMPID_DECL__(ecs::cmp::POKEBALL_EFFECT);
};
}