#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class BoxRBComponent : public RigidBodyComponent
    {
    public:
        BoxRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, float length, bool sensor = false, b2Rot rotation = defaultRotation, float density = 1, float friction = 0.2, float restitution = 1, float linearDamping = 0.45f, bool bullet = false);

        void setScale(const Scale& newScale) override;
    };
}