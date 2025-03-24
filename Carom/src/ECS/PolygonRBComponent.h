#pragma once
#include "RigidBodyComponent.h"
#include <vector>

namespace ecs{
    class PolygonRBComponent : public RigidBodyComponent
    {
    public:
        PolygonRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, 
            const std::vector<b2Vec2> &vertices, float radius = 0, bool sensor = false, 
            b2Rot rotation = defaultRotation, float density = 1, float friction = 0.2, 
            float restitution = 1, float linearDamping = 0.45f, bool bullet = false);
            ~PolygonRBComponent();

    protected:
        void updateScale() override;
    };
}