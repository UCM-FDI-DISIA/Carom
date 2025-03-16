#include <Vector2D.h>

#include "Entity.h"
#include "GameScene.h"
#include "FrictionComponent.h"
#include "WhiteBallScorerComponent.h"


namespace ecs{

    FrictionComponent::FrictionComponent(entity_t ent)
        : PhysicsComponent(ent)
    {
    }

    // Apply friction force to bodies inside area proportional to its mass
    // Force applied only for moving entities
    void FrictionComponent::update()
    {
        applyForceToAll();
    }

    void FrictionComponent::onTriggerEnter(entity_t other)
    {
        if(other->tryGetComponent<RigidBodyComponent>()){
            _rigidbodies.insert_or_assign(other, true);
            applyForce(other); // applies force on enter for cases in which fast balls could skip an update
        }
    }

    void FrictionComponent::onTriggerExit(entity_t other)
    {
        _rigidbodies[other] = false;
    }

    void FrictionComponent::applyForceToAll()
    {
        for(auto it = _rigidbodies.begin(); it != _rigidbodies.end(); ++it){
            entity_t entity = (*it).first;
            bool isInside = (*it).second;
            if (isInside)
                applyForce(entity);
        }
    }

    void FrictionComponent::applyForce(entity_t e)
    {
        auto rb = e->getComponent<RigidBodyComponent>();

        if(bodyIsMoving(*rb)){

            float    a_bodyMass = rb->getMass();
            Vector2D a_bodyVel = {rb->getVelocity().x, rb->getVelocity().y};
            Vector2D a_frictionForce = a_bodyVel.normalize() * (-1) * _mu * a_bodyMass * _g;
            rb->applyForceToCenter({a_frictionForce.getX(), a_frictionForce.getY()});

            if (e->tryGetComponent<WhiteBallScorerComponent>()){
                // TODO: camera shake
            }
        }
    }

    // Less restrictive than RB::isMoving() because friction force can introduce small movements
    bool FrictionComponent::bodyIsMoving(RigidBodyComponent &rb) {
        b2Vec2 vel = rb.getVelocity();
        return std::sqrt(std::pow(vel.x, 2) + std::pow(vel.y, 2)) > 0.025f;
    }

}
