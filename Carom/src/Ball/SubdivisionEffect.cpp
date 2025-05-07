#include "SubdivisionEffect.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StickInputComponent.h"
#include "BallHandler.h"
#include "CaromScene.h"

void
SubdivisionEffect::onStrikeEnd(){
    _target->activate();
    _target->getTransform()->setPosition(_myEntity->getTransform()->getPosition());
    _myEntity->deactivate();
    dynamic_cast<CaromScene&>(_myEntity->getScene()).activateIndicator();
}