#include "SubdivisionEffect.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StickInputComponent.h"
#include "BallHandler.h"
#include "GameScene.h"

using namespace ecs;

void
SubdivisionEffect::onStrikeEnd(){
    _target->activate();
    _target->getTransform()->setPosition(_myEntity->getTransform()->getPosition());
    // TODO Elimina la entidad
}