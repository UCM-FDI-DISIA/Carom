#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class HandleEventComponent : public Component
    {
    public:
        HandleEventComponent(Entity* ent) : Component(ent) {}
        virtual ~HandleEventComponent(){}
    
        void update() override {}
        void render(Camera*) override {}
    };
}