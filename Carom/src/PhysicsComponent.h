#pragma once
#include "Component.h"
class Entity;

class PhysicsComponent : public Component
{
public:
    virtual ~PhysicsComponent(){}

    virtual void update(Entity* e) = 0;
    void render(Entity* e) {}
    void handleEvent(Entity* e) {}
};