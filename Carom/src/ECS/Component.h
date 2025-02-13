#pragma once

#include "ecs.h"

namespace ecs
{
    class Entity;
    
    class Component
    {
    public:
        Component(Entity* e) : _e(e) {}
        virtual ~Component() {}

        virtual void init(Entity*) = 0;

        inline void setContext(entity_t e) {
            _e = e;
        };

        virtual void update(Entity*) = 0;
        virtual void render(Entity*) = 0;
        virtual void handleEvent(Entity*) = 0;

    protected: // we allow direct use these fields from subclasses
	    entity_t _e; // a pointer to the entity, should not be deleted on destruction
    };
}