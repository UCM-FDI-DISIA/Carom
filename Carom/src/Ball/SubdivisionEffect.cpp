#include "SubdivisionEffect.h"
#include "Entity.h"
#include "TransformComponent.h"

using namespace ecs;

void
SubdivisionEffect::onStrikeEnd(){
    _target->activate();
    _target->getTransform()->setPosition(_myEntity->getTransform()->getPosition());
    delete _myEntity;
}