#include "PhysicsComponent.h"
#include "Entity.h"
#include "RigidBodyComponent.h"

PhysicsComponent::PhysicsComponent(entity_t ent) : Component(ent){
    assert(ent->tryGetComponent<RigidBodyComponent>());

    ent->getComponent<RigidBodyComponent>()->suscribePhysicsComponent(this);
}

PhysicsComponent::~PhysicsComponent() {_onDestroy();}