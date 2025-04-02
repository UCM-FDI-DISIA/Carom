#pragma once

#include "BallEffect.h"
#include "PhysicsUtils.h"

namespace ecs{
class ITransform;
}

class PopToOppositeSideEffect : public BallEffect{

    ecs::ITransform* _mTrans;

    //Positions of the table
    b2Vec2 _leftPos;
    b2Vec2 _rightPos;
    b2Vec2 _topPos;
    b2Vec2 _botPos;

public:
__CMPID_DECL__(ecs::cmp::POP_TO_OPPOSITE_EFFECT);

    inline PopToOppositeSideEffect(ecs::entity_t ent) : BallEffect(ent) {}
    inline ~PopToOppositeSideEffect() {}

    void init() override;

    inline ecs::cmpId_t getEffectId() override {return ecs::cmp::POP_TO_OPPOSITE_EFFECT;}
    void onStrikeEnd() override;
    void popOnCollision(ecs::entity_t other);
};