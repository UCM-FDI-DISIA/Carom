#include "TryCollisionComponent.h"
#include <iostream>

using namespace ecs;

TryCollisionComponent::TryCollisionComponent(entity_t ent) : PhysicsComponent(ent)
{
}

void
TryCollisionComponent::onCollisionEnter(entity_t other){
    std::cout << "Colision" << std::endl;
}