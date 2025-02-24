#include "PhysicsComponent.h"
#include "Entity.h"
#include "RigidBodyComponent.h"

using namespace ecs;

ecs::PhysicsComponent::PhysicsComponent(entity_t ent) : Component(ent){
    assert(ent->tryGetComponent<RigidBodyComponent>());

    ent->getComponent<RigidBodyComponent>()->suscribePhysicsComponent(this);
}