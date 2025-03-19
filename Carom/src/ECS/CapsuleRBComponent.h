#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class CapsuleRBComponent : public RigidBodyComponent
    {
    public:
        CapsuleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, float width, 
            float height, bool sensor = false, b2Rot rotation = defaultRotation, float density = 1, 
            float friction = 0.2, float restitution = 1, float linearDamping = 0.45f, bool bullet = false);

    protected:
        void updateScale() override;
    };
}