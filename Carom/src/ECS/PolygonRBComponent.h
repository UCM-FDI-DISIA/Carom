#pragma once
#include "RigidBodyComponent.h"
#include <vector>

namespace ecs{
    class PolygonRBComponent : public RigidBodyComponent
    {
        std::vector<b2Vec2> _vertices;
        int _radius;

    public:
        PolygonRBComponent(entity_t ent, const Vector2D& pos, b2BodyType type, const std::vector<b2Vec2> &vertices, float density = 1, float friction = 0.2, float restitution = 0.5, float radius = 0);

        void setScale(const Scale& newScale) override;
    };
}