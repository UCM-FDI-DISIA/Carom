#include "QuanticEffect.h"
#include "CaromScene.h"

void QuanticEffect::init()
{
    BallEffect::init();
}

//Registra que ha sido golpeada
void QuanticEffect::onHit(entity_t ent)
{
    _wasHit = true;
}

//Al final del tiro, si no ha sido golpeada, multiplica la puntuación por 2
void QuanticEffect::onStrikeEnd()
{
    if(!_wasHit)
    {
        _handler->multRoundScore(2 * _handler->getMult());
    }
    else _wasHit = false;
}