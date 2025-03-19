#pragma once
#include "AbacusEffect.h"
#include "Entity.h"
#include "BallHandler.h"


void AbacusEffect::init()
{
    BallEffect::init();
    _handler = _myEntity->getComponent<ecs::BallHandler>();
}

void AbacusEffect::onHit(ecs::entity_t ent)
{
    _handler->addScore(_bonusPoints);
}