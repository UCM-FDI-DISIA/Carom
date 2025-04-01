#pragma once
#include "Component.h"
class Entity;

class RenderComponent : public Component
{
public:
    RenderComponent(Entity* ent) : Component(ent) {}
    virtual ~RenderComponent(){}

    void update() override {}
    void handleEvent() override {}
};