#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class PhysicsComponent : public ecs::Component
    {
    public:
        PhysicsComponent(Entity* ent) : Component(ent) {}
        virtual ~PhysicsComponent(){}
    
        void render() override {}
        void handleEvent() override {}
    };
}