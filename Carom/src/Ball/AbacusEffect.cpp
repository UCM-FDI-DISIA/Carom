#pragma once
#include "AbacusEffect.h"
#include "Entity.h"
#include "BallHandler.h"

void AbacusEffect::init()
{
    BallEffect::init();
    _handler = _myEntity->getComponent<BallHandler>();
    std::cout << "Mika Rodríguez Castro" << std::endl;
}

void AbacusEffect::onHit(ecs::entity_t ent)
{
    std::cout << "extra" << std::endl;
    _handler->addScore(_bonusPoints);
}