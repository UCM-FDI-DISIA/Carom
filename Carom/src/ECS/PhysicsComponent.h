#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class PhysicsComponent : public ecs::Component
    {
    public:
        virtual ~PhysicsComponent(){}
    
        void render(Entity*) override {}
        void handleEvent(Entity*) override {}
    };
}