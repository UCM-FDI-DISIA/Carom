#pragma once
#include "ecs.h"

class Camera;
namespace ecs
{
    class Component
    {
    protected:
        entity_t _myEntity;
        bool _isEnable;
    public:
        Component(entity_t ent);
        virtual ~Component() = 0;

        virtual void init() = 0;

        virtual void update() = 0;
        virtual void render(Camera*) = 0;
        virtual void handleEvent() = 0;

        virtual void setEnabled(bool state);
        bool isEnabled();
    };
}