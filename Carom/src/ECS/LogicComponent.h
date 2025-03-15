#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class LogicComponent : public Component
    {
    public:
        LogicComponent(Entity* ent) : Component(ent) {}
        virtual ~LogicComponent(){}
    
        void render() override {}
        void handleEvent() override {}
    };
}