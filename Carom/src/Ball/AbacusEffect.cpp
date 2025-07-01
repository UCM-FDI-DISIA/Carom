#include "AbacusEffect.h"
#include "Entity.h"
#include "BallHandler.h"

//Se suma puntuación extra al ser golpeada
void AbacusEffect::onHit(entity_t ent)
{
    _handler->addScore(_bonusPoints);
}