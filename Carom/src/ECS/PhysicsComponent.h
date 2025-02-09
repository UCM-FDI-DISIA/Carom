#pragma once
#include "Component.h"
class Entity;

class PhysicsComponent : public ecs::Component
{
public:
    virtual ~PhysicsComponent(){}

    virtual void update(Entity* e) = 0;
    void render(Entity* e) override {}
    void handleEvent(Entity* e) override {}
};