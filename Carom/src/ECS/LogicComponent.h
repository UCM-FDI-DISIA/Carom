#pragma once
#include "Component.h"
class Entity;

class LogicComponent : public Component
{
public:
    LogicComponent(Entity* ent) : Component(ent) {}
    virtual ~LogicComponent(){}

    void render(Camera*) override {}
    void handleEvent() override {}
};
