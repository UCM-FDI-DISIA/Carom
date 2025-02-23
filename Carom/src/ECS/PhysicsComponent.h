#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class PhysicsComponent : public Component
    {
    public:
        PhysicsComponent(Entity* ent) : Component(ent) {}
        virtual ~PhysicsComponent(){}
    
        void render(Camera*) override {}
        void handleEvent() override {}
    };
}