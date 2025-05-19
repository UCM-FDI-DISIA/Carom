#include "X2Effect.h"
#include "BallHandler.h"
#include "Entity.h"

//Al ser añadida amplifica la intensidad de los efectos de la bola multiplicando el multiplicador por 2
void X2Effect::init()
{
    BallEffect::init();
    _handler->setMult(_handler->getMult() * 2);
}