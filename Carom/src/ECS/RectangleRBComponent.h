#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class RectangleRBComponent : public RigidBodyComponent
    {
        float _width;
        float _height;
    public:
        RectangleRBComponent(entity_t ent, const Vector2D& pos, b2BodyType type, float width, float height, float density = 1, float friction = 0.2, float restitution = 0.5);

        void setScale(const Scale& newScale) override;
    };
}