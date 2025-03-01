#include "TryCollisionComponent.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include <iostream>

using namespace ecs;

TryCollisionComponent::TryCollisionComponent(entity_t ent) : PhysicsComponent(ent)
{
}

void
TryCollisionComponent::onCollisionEnter(entity_t other){
}