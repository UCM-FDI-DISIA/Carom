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

    inline PopToOppositeSideEffect(BallHandler* hndlr) : BallEffect(hndlr) {}
    inline ~PopToOppositeSideEffect() {}

    void init() override;

    __EFFID_DECL__(effect::POP_TO_OPPOSITE_EFFECT);
    inline effectId_t getEffectId() override {return effect::POP_TO_OPPOSITE_EFFECT;}
    void onStrikeEnd() override;
    void popOnCollision(entity_t other);
};