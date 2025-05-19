#include "AbacusEffect.h"
#include "Entity.h"
#include "BallHandler.h"

void AbacusEffect::init()
{
    BallEffect::init();
    _handler = _myEntity->getComponent<BallHandler>();
}

//Se suma puntuación extra al ser golpeada
void AbacusEffect::onHit(entity_t ent)
{
    _handler->addScore(_bonusPoints);
}