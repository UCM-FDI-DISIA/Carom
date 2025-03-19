#pragma once
#include "BowlingEffect.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
using namespace ecs;

void BowlingEffect::init()
{
    assert(_myEntity->tryGetComponent<ecs::RigidBodyComponent>() || "Se está intentando añadir el componente BowlingEffect a una entidad sin rigibody");

    ecs::RigidBodyComponent* rb =_myEntity->getComponent<ecs::RigidBodyComponent>();
    rb->setDensity(DENSITY);
    rb->setFriction(FRICTION);
}