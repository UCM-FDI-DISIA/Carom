#pragma once

namespace ecs
{
    class Entity;
    
    class Component
    {
    protected:
        Entity* _myEntity;
    public:
        Component(Entity* ent) : _myEntity(ent) {}
        virtual ~Component() = 0;

        virtual void init() = 0;

        virtual void update() = 0;
        virtual void render() = 0;
        virtual void handleEvent() = 0;
    };
}