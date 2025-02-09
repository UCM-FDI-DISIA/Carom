#pragma once
#include "Component.h"
class Entity;

class RenderComponent : public ecs::Component
{
public:
    virtual ~RenderComponent(){}

    void update(Entity* e) override {}
    virtual void render(Entity* e) = 0;
    void handleEvent(Entity* e) override {}
};