#pragma once
#include "BowlingEffect.h"
#include "RigidBodyComponent.h"
#include "Entity.h"

void BowlingEffect::init()
{
    ecs::RigidBodyComponent* rb;
    assert(_myEntity->tryGetComponent<ecs::RigidBodyComponent>(rb) || "Se está intentando añadir el componente BowlingEffect a una entidad sin rigibody");
    rb->setDensity(DENSITY);
    rb->setFriction(FRICTION);
}