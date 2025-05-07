#include "PetanqueEffect.h"
#include "Entity.h"
#include "GameScene.h"
#include "BallHandler.h"
#include "math.h"

void PetanqueEffect::init()
{
    BallEffect::init();
}

void PetanqueEffect::onStrikeEnd()
{
    entity_t _whiteBall = _myEntity->getScene().getEntitiesOfGroup(grp::WHITEBALL)[0];
    float distance = b2Distance(_myEntity->getTransform()->getPosition(), _whiteBall->getTransform()->getPosition());
    _handler->multScore(b2ClampFloat(2 * (1 - b2ClampFloat((distance/ MAX_DISTANCE), 0, 1)), 1, 2) * _handler->getMult());
}