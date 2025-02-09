#pragma once
#include "Component.h"
class Entity;

class HandleEventComponent : public ecs::Component
{
public:
    virtual ~HandleEventComponent(){}

    void update(Entity* e) override {}
    void render(Entity* e) override {}
    void handleEvent(Entity* e) = 0;
};