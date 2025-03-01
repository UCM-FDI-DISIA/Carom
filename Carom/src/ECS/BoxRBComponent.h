#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class BoxRBComponent : public RigidBodyComponent
    {
        float _length;
    public:
        BoxRBComponent(entity_t ent, const Vector2D& pos, b2BodyType type, float length, float density = 1, float friction = 0.2, float restitution = 0.5);

        void setScale(const Scale& newScale) override;
    };
}