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
    _myEntity->deactivate();
    _myEntity->setAlive(false); // * Te juro que en cuanto traigamos la rama de Andrea funciona
}