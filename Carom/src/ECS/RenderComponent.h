#pragma once
#include "Component.h"
class Entity;

namespace ecs{
    class RenderComponent : public ecs::Component
    {
    public:
        virtual ~RenderComponent(){}

        void update(Entity*) override {}
        void handleEvent(Entity*) override {}
    };
}