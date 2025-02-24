#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"

namespace ecs{
    class TryCollisionComponent : public PhysicsComponent{
        public:
        __CMPID_DECL__(cmp::TRYCOLLISION);

        TryCollisionComponent(entity_t ent);

        void onCollisionEnter(entity_t other);
    };
}