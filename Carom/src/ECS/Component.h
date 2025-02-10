#pragma once

namespace ecs
{
    class Entity;
    
    class Component
    {
    public:
        Component() {}
        virtual ~Component() = 0;

        virtual void init(Entity*) = 0;

        virtual void update(Entity*) = 0;
        virtual void render(Entity*) = 0;
        virtual void handleEvent(Entity*) = 0;
    };
}