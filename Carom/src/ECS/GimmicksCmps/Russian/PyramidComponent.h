#pragma once

#include "ForceFieldComponent.h"
#include "RenderTextureComponent.h"
#include "Vector2D.h"


using isInsideField = bool;


class PyramidComponent : public ForceFieldComponent
{
protected:
    double _slope; // 45 degrees
    b2Vec2 _direction; // force direction

public:
    __CMPID_DECL__(cmp::PYRAMID);

    PyramidComponent(entity_t ent, const b2Vec2& direction, float slope = M_PI/3.0);
    ~PyramidComponent() {}
    
protected:
    virtual void calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction) override;
    virtual void applyForce(RigidBodyComponent* rb) override;
};
