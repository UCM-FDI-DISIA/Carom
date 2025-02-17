#pragma once
#include "Component.h"
class Entity;

namespace ecs{
    class RenderComponent : public Component
    {
    public:
        RenderComponent(Entity* ent) : Component(ent) {}
        virtual ~RenderComponent(){}

        void update() override {}
        void handleEvent() override {}
    };
}