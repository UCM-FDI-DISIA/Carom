#pragma once
#include "Component.h"
class Entity;

namespace ecs {
    class HandleEventComponent : public ecs::Component
    {
    public:
        virtual ~HandleEventComponent(){}
    
        void update(Entity*) override {}
        void render(Entity*) override {}
        void handleEvent(Entity*) = 0;
    };
}