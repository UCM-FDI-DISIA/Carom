#include "PetanqueEffect.h"
#include "Entity.h"
#include "GameScene.h"
#include "BallHandler.h"

void PetanqueEffect::init()
{
    BallEffect::init();
}

void PetanqueEffect::onStrikeEnd()
{
    entity_t _whiteBall = _myEntity->getScene().getEntitiesOfGroup(grp::WHITEBALL)[0];
    float distance = b2Distance(_myEntity->getTransform()->getPosition(), _whiteBall->getTransform()->getPosition());
    _handler->multScore(MAX_DISTANCE * _handler->getMult()/ distance * _handler->getMult());
}