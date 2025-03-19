#pragma once
#include "QuanticEffect.h"
#include "CaromScene.h"

void QuanticEffect::init()
{
    BallEffect::init();
}

void QuanticEffect::onHit(ecs::entity_t ent)
{
    _wasHit = true;
}

void QuanticEffect::onStrikeEnd()
{
    if(!_wasHit)
    {
        _handler->multScore(2);
    }
    else _wasHit = false;
}