#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class CircleRBComponent : public RigidBodyComponent
    {
        float _radius;
    public:
        CircleRBComponent(entity_t ent, const Vector2D& pos, b2BodyType type, float radius, float density = 1, float friction = 0.2, float restitution = 0.5);

        void setScale(const Scale& newScale) override;
    };
}