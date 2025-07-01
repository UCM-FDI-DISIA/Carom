#pragma once

#include "BallEffect.h"
#include <iostream>


class SubdivisionEffect : public BallEffect{
    entity_t _target;
public:
    __EFFID_DECL__(effect::SUBDIVISION_EFFECT);
    effectId_t getEffectId() override {return effect::SUBDIVISION_EFFECT;};

    SubdivisionEffect(BallHandler* hndlr, entity_t target) : BallEffect(hndlr), _target(target) {}
    ~SubdivisionEffect() {}
    void onStrikeEnd() override;
};
