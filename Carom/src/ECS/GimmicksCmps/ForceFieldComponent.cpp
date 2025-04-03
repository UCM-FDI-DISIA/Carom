#include "Entity.h"
#include "ForceFieldComponent.h"
#include "RigidBodyComponent.h"
#include "RenderTextureComponent.h"
#include "PhysicsUtils.h"



ForceFieldComponent::ForceFieldComponent(entity_t ent) 
    : PhysicsComponent(ent)
{
    _myRB = _myEntity->getComponent<RigidBodyComponent>();
    _myRadius = PhysicsConverter::pixel2meter(_myEntity->getComponent<RenderTextureComponent>()->getRect().w/2);
    _myForce = b2Vec2_zero;

    _minForce = 0;
    _maxForce = SDL_MAX_UINT8; // 255
    _minVelocity = 0;
    _maxVelocity = SDL_MAX_UINT8; // 255
}

// Apply defined force by derived to all bodies registered
void ForceFieldComponent::update()
{
    applyForceToAll();
}

// Registers body and applies force on enter for cases in which fast bodies could skip an update
void ForceFieldComponent::onTriggerEnter(entity_t other)
{
    if(other->tryGetComponent<RigidBodyComponent>()){
        _rigidbodies.insert_or_assign(other, true);
        applyForce(other); 
    }
}

// ! _rigidbodies: bodies are not erased, only set to out for pragmatic reasons (box2d issues vs. memory overhead)
void ForceFieldComponent::onTriggerExit(entity_t other)
{
    _rigidbodies[other] = false;
}

// Apply force to all bodies registered and flagged inside
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