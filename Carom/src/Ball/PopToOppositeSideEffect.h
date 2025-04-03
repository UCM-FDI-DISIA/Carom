#pragma once

#include "BallEffect.h"
#include "PhysicsUtils.h"

class ITransform;

class PopToOppositeSideEffect : public BallEffect{

    ITransform* _mTrans;

    //Positions of the table
    b2Vec2 _leftPos;
    b2Vec2 _rightPos;
    b2Vec2 _topPos;
    b2Vec2 _botPos;

public:
__CMPID_DECL__(cmp::POP_TO_OPPOSITE_EFFECT);

    inline PopToOppositeSideEffect(entity_t ent) : BallEffect(ent) {}
    inline ~PopToOppositeSideEffect() {}

    void init() override;

    inline cmpId_t getEffectId() override {return cmp::POP_TO_OPPOSITE_EFFECT;}
    void onStrikeEnd() override;
    void popOnCollision(entity_t other);
};