#pragma once
#include "PetanqueEffect.h"
#include "Entity.h"
#include "GameScene.h"
#include "BallHandler.h"

void PetanqueEffect::init()
{
    BallEffect::init();
    _handler = _myEntity->getComponent<BallHandler>();
    _whiteBall = _myEntity->getScene().getEntitiesOfGroup(ecs::grp::WHITEBALL)[0];
}

void PetanqueEffect::onStrikeEnd()
{
    float distance = b2Distance(_myEntity->getTransform()->getPosition(), _whiteBall->getTransform()->getPosition());
    _handler->multScore(MAX_DISTANCE/distance);
}