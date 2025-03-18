#pragma once

#include <box2d/box2d.h>
#include <unordered_map>
#include "ecs.h"

#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"


using isInsideField = bool;

namespace ecs{

    class Entity;
    // Abstract component class for entities that induce force on other entities within its bounderies
    // A force defined is derived classes are applied to all entities inside the area of the sensor
    class ForceFieldComponent : public PhysicsComponent
    { 
    protected:
        std::unordered_map<entity_t, isInsideField> _rigidbodies;
        RigidBodyComponent* _myRB;
        float _myRadius;
        b2Vec2 _force;
        float _maxForce;

        float _maxVelocity = -1; // above that no force is applied because of the simulation lag that makes it unrealistic at high speed. -1 is for no maxVelocity
        
    public:
        ForceFieldComponent(entity_t ent);
        ~ForceFieldComponent() {}

    protected:
        virtual void update();
        virtual void onTriggerEnter(entity_t other) override;
        virtual void onTriggerExit(entity_t other) override; 

        virtual void applyForce(entity_t e, b2Vec2 force) = 0;
        virtual void applyForceToAll();
        virtual bool bodyIsMoving(RigidBodyComponent &rb);
    };

}
