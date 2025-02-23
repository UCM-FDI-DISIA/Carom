#pragma once

class Camera;
namespace ecs
{
    class Entity;
    class Component
    {
    protected:
        Entity* _myEntity;
    public:
        inline Component(Entity* ent) : _myEntity(ent) {}
        virtual ~Component() = 0;

        virtual void init() = 0;

        virtual void update() = 0;
        virtual void render(Camera*) = 0;
        virtual void handleEvent() = 0;
    };
}