#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "B2Manager.h"
#include <exception>

using namespace ecs;

RigidBodyComponent::RigidBodyComponent(Entity* ent) : PhysicsComponent(ent) 
{
    // Initialitation of Manager, Transform and entity
    _manager = B2Manager::Instance();
    try {assert(ent->tryGetComponent<TransformComponent>(ecs::TRANSFORM, _transform));}
    catch(std::exception) { throw std::exception("Trying to attach a RigidBody to an Entity without Transform"); }
    _myEntity = ent;
}

