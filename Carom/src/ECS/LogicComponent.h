#pragma once

#include "Component.h"

class Entity;

class LogicComponent : public Component
{
public:
    LogicComponent(Entity* ent) : Component(ent) {}
        virtual ~LogicComponent(){}

        void render() override {}
        void handleEvent() override {}
};