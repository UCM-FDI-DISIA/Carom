#include "SubdivisionEffect.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StickInputComponent.h"
#include "BallHandler.h"
#include "CaromScene.h"

/// @brief Teleports the original ball to its position and destroys itself
void
SubdivisionEffect::onStrikeEnd(){
    _target->activate();
    _target->getTransform()->setPosition(_handler->_myEntity->getTransform()->getPosition());
    _handler->_myEntity->deactivate();
    dynamic_cast<CaromScene&>(_handler->_myEntity->getScene()).activateIndicator();
}