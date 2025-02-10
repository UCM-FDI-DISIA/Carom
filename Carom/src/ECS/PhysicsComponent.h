#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class PhysicsComponent : public ecs::Component
    {
    public:
        virtual ~PhysicsComponent(){}
    
        virtual void update(Entity*) = 0;
        void render(Entity*) override {}
        void handleEvent(Entity*) override {}
    };
}