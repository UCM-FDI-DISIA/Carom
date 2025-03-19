#pragma once
#include "QuanticEffect.h"
#include "CaromScene.h"
using namespace ecs;

void QuanticEffect::init()
{
    BallEffect::init();
    _handler = _myEntity->getComponent<BallHandler>();
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