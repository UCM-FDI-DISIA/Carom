#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class HandleEventComponent : public ecs::Component
    {
    public:
        HandleEventComponent(Entity* ent) : Component(ent) {}
        virtual ~HandleEventComponent(){}
    
        void update() override {}
        void render() override {}
    };
}