#pragma once

#include "RigidBodyComponent.h"

// Componente de rigidbody para objetos circulares (bolas)
class CircleRBComponent : public RigidBodyComponent 
{
public:
    CircleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType type, float radius, 
        bool sensor = false, b2Rot rotation = defaultRotation, float density = 1, 
        float friction = 0.2, float restitution = 1, float linearDamping = 0.45f, 
        bool bullet = true);

    void calculateMass() override;
    void setSize(float newSize) override;

    inline float getRadius() const { return _myProps.radius;}

protected:
    void updateScale() override;

    float _initialRadius;
};