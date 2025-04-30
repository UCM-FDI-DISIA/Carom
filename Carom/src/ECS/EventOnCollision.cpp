#include "EventOnCollision.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include <iostream>

EventOnCollision::EventOnCollision(entity_t ent) : PhysicsComponent(ent)
{
    _onCollisionEnter = [this](entity_t entity, b2Manifold& contactData) { std::cout << "Entered with " << entity << std::endl; };
    _onCollisionExit = [this](entity_t entity) { std::cout << "Exited with " << entity << std::endl; };
}

EventOnCollision::EventOnCollision(entity_t ent, std::function<void(entity_t, b2Manifold&)> enter, std::function<void(entity_t)> exit) : PhysicsComponent(ent)
{
    _onCollisionEnter = enter;
    _onCollisionExit = exit;
}

void
EventOnCollision::onCollisionEnter(entity_t other, b2Manifold& contactData){
    _onCollisionEnter(other, contactData);
}

void EventOnCollision::onCollisionExit(entity_t other){
    _onCollisionExit(other);
}