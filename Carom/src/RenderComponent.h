#pragma once
#include "Component.h"
class Entity;

class RenderComponent : public Component
{
public:
    virtual ~RenderComponent(){}

    virtual void update(Entity* e) {}
    void render(Entity* e) = 0;
    void handleEvent(Entity* e) {}
};