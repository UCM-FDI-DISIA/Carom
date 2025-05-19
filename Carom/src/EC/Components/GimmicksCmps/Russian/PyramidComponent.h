#pragma once

#include "ForceFieldComponent.h"
#include "RenderTextureComponent.h"
#include "Vector2D.h"


using isInsideField = bool;

// Componente de pirámide. Simula una inclinación al aplicar fuerza en una dirección a la bola
class PyramidComponent : public ForceFieldComponent
{
protected:
    double _slope;
    b2Vec2 _direction; // force direction

public:
    __CMPID_DECL__(cmp::PYRAMID);

    PyramidComponent(entity_t ent, const b2Vec2& direction, float slope = M_PI/3.0);
    ~PyramidComponent() {}
    
protected:
    virtual void calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction) override;
    virtual void applyForce(RigidBodyComponent* rb) override;
};
