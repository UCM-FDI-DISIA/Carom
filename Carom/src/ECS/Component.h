#pragma once

namespace ecs
{
    class Entity;
    
    class Component
    {
    protected:
        Entity* _myEntity;
        bool _active;
    public:
        Component(Entity* ent);
        virtual ~Component() = 0;

        virtual void init() = 0;

        virtual void update() = 0;
        virtual void render() = 0;
        virtual void handleEvent() = 0;

        void setEnable(bool state);
        bool isEnable();
    };
}