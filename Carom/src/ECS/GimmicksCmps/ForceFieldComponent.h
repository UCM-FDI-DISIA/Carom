#pragma once

#include <box2d/box2d.h>
#include <unordered_map>
#include "ecs.h"

#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"


using isInsideField = bool;

namespace ecs{

    // Abstract component class for entities that induce force on other entities within its bounderies
    // A force defined is derived classes are applied to all entities inside the area of the sensor
    class ForceFieldComponent : public PhysicsComponent
    { 
    protected:
        std::unordered_map<entity_t, isInsideField> _rigidbodies;
        RigidBodyComponent* _myRB;
        
    public:
        ForceFieldComponent(entity_t ent);
        ~ForceFieldComponent() {}

    protected:
        virtual void update();
        virtual void onTriggerEnter(entity_t other) override;
        virtual void onTriggerExit(entity_t other) override; 

        virtual void applyForce(entity_t e) = 0;
        virtual void applyForceToAll();
        virtual bool bodyIsMoving(RigidBodyComponent &rb);
    };

}
