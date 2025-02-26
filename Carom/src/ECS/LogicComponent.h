#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class LogicComponent : public Component
    {
    public:
        LogicComponent(Entity* ent) : Component(ent) {}
        virtual ~LogicComponent(){}
    
        void render(Camera*) override {}
        void handleEvent() override {}
    };
}