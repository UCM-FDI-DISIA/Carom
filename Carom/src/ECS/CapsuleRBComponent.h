#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class CapsuleRBComponent : public RigidBodyComponent
    {
        float _radius;
        b2Vec2 _center1;
        b2Vec2 _center2;
    public:
        CapsuleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType type, float radius, b2Vec2 center1, b2Vec2 center2, float density = 1, float friction = 0.2, float restitution = 0.5);

        void setScale(const Scale& newScale) override;
    };
}