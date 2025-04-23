#pragma once

#include "ForceFieldComponent.h"


// Component to be added to an entity with RB set to sensor
// Objects inside recieve a counter force during motion
// It doesn't use linearDamping for 2 reasons:
// - Avoiding conflict with stick ability
// - Reuse logic to force field like components
class FrictionComponent : public ForceFieldComponent
{ 
    float _mu; // friction coeficient (no distinction dynamic/static)
    
public:
    __CMPID_DECL__(cmp::FRICTION);
    
    FrictionComponent(entity_t ent, float frictionCoef = 2);
    virtual ~FrictionComponent() {}
    
protected:
    virtual void applyForce(RigidBodyComponent* rb) override;
    virtual void calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction);
};