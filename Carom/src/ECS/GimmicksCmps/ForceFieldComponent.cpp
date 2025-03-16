#include "Entity.h"
#include "ForceFieldComponent.h"
#include "RigidBodyComponent.h"


namespace ecs{

    ForceFieldComponent::ForceFieldComponent(entity_t ent) 
        : PhysicsComponent(ent)
    {
        _myRB = _myEntity->getComponent<RigidBodyComponent>();
    }

    // Apply friction force to bodies inside area proportional to its mass
    // Force applied only for moving entities
    void ForceFieldComponent::update()
    {
        applyForceToAll();
    }

    void ForceFieldComponent::onTriggerEnter(entity_t other)
    {
        if(other->tryGetComponent<RigidBodyComponent>()){
            _rigidbodies.insert_or_assign(other, true);
            applyForce(other); // applies force on enter for cases in which fast balls could skip an update
        }
    }

    // ! _rigidbodies: bodies are not erased, only set to out for pragmatic reasons (box2d issues vs. memory overhead)
    void ForceFieldComponent::onTriggerExit(entity_t other)
    {
        _rigidbodies[other] = false;
    }

    void ForceFieldComponent::applyForceToAll()
    {
        for(auto it = _rigidbodies.begin(); it != _rigidbodies.end(); ++it){
            entity_t entity = (*it).first;
            bool isInside = (*it).second;
            if (isInside)
                applyForce(entity);
        }
    }

    // Less restrictive than RB::isMoving() because friction force can introduce small movements
    bool ForceFieldComponent::bodyIsMoving(RigidBodyComponent &rb) {
        b2Vec2 vel = rb.getVelocity();
        return std::sqrt(std::pow(vel.x, 2) + std::pow(vel.y, 2)) > 0.025f;
    }

}