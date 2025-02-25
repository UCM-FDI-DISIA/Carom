#pragma once
#include "ecs.h"

class Camera;
namespace ecs
{
    class Component
    {
    protected:
        entity_t _myEntity;
    public:
        inline Component(entity_t ent) : _myEntity(ent) {}
        virtual ~Component() = 0;

        virtual void init() = 0;

        virtual void update() = 0;
        virtual void render(Camera*) = 0;
        virtual void handleEvent() = 0;
    };
}