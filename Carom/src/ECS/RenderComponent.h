#pragma once
#include "Component.h"

class Entity;

namespace ecs{
    class RenderComponent : public Component
    {
    public:
        RenderComponent(Entity* entity) : Component(entity) {}
        virtual ~RenderComponent(){}

        void update(Entity* entity) override {}
        void handleEvent(Entity* entity) override {}

        void init(Entity* entity) override {}
        void render(Entity* entity) override {}
    };
}