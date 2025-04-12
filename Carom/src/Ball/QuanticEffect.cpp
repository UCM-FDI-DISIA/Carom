#include "QuanticEffect.h"
#include "CaromScene.h"

void QuanticEffect::init()
{
    BallEffect::init();
}

void QuanticEffect::onHit(entity_t ent)
{
    _wasHit = true;
}

void QuanticEffect::onStrikeEnd()
{
    if(!_wasHit)
    {
        _handler->multScore(2 * _handler->getMult());
    }
    else _wasHit = false;
}