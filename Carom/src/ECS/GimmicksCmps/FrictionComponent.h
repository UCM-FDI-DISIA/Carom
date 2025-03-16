#pragma once
#include <box2d/box2d.h>
#include "ecs.h"
#include <unordered_map>

#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"

using isInside = bool;

namespace ecs{

    // Component to be added to an entity with RB set to sensor
    // Objects inside recieve a counter force during motion
    class FrictionComponent : public PhysicsComponent
    { 
        std::unordered_map<entity_t, isInside> _rigidbodies; // bodies are not erased, only set to out for pragmatic reasons
        float _mu = 1.0f; // friction coeficient (no distinction dynamic/static)
        const float _g = 9.8f; // """"gravity""""
        
    public:
        __CMPID_DECL__(cmp::FRICTION);
        
        FrictionComponent(entity_t ent);

        void update() override;
        void onTriggerEnter(entity_t other) override;
        void onTriggerExit(entity_t other) override;

    protected:
        void applyForceToAll();
        void applyForce(entity_t e);
        bool bodyIsMoving(RigidBodyComponent &rb);

    };

}