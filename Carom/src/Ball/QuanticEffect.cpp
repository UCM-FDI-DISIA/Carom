#pragma once
#include "QuanticEffect.h"
#include "CaromScene.h"

void QuanticEffect::onHit(ecs::entity_t ent)
{
    _wasHit = true;
}

void QuanticEffect::onStrikeEnd()
{
    if(!_wasHit)
    {
        _scene->addScore(_scene->getCurrentScore());
    }
    else _wasHit = false;
}