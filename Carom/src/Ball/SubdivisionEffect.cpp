#include "SubdivisionEffect.h"
#include "Entity.h"
#include "TransformComponent.h"

using namespace ecs;

void
SubdivisionEffect::onStrikeEnd(){
    _target->getTransform()->setPosition(_myEntity->getTransform()->getPosition());
    _target->activate();
    delete _myEntity;
}