#pragma once

#include <box2d/box2d.h>
#include <unordered_map>
#include "ecs.h"

#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"


using isInsideField = bool;

class Vector2D;
class Entity;
// Abstract component class for entities that induce force on other entities within its bounderies
// Registers entities with RB on trigger enter.
// Flags as isInside = true when enter and false on exit trigger
// A force defined in derived classes are applied to all entities registered
class ForceFieldComponent : public PhysicsComponent
{ 
protected:
    // bodies are registered and flagged isInside the sensor
    std::unordered_map<entity_t, isInsideField> _rigidbodies {};

    RigidBodyComponent* _myRB;
    float _myRadius; // radius in meters of the sensor
    b2Vec2 _myForce; // force applied to bodies

    const float _g = 9.8f; // """"gravity""""

    float _minForce;
    float _maxForce; // cap
    float _minVelocity; // default = 0 => no bottom bounderies for velocity of a body to apply a force 
    float _maxVelocity; // above it no force is applied because of the simulation lag that makes it unrealistic at high speed. The force would be applied out of context, outside sensor area
    
public:
    ForceFieldComponent(entity_t ent);
    ~ForceFieldComponent() {}

protected:
    virtual void update();
    virtual void onTriggerEnter(entity_t other) override;
    virtual void onTriggerExit(entity_t other) override; 

    virtual void calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction) {}
    virtual void applyForce(RigidBodyComponent* rb);
    virtual void applyForceToAll();
    virtual bool bodyIsMoving(RigidBodyComponent &rb);
};
