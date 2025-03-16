#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class CircleRBComponent : public RigidBodyComponent
    {
    public:
        CircleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType type, float radius, bool sensor = false, b2Rot rotation = defaultRotation, float density = 1, float friction = 0.2, float restitution = 1, float linearDamping = 0.45f, bool bullet = true);

        void setScale(const Scale& newScale) override;
        void calculateMass() override;
    };
}