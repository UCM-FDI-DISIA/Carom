#include "PushOutsideTriggerComponent.h"

#include "Entity.h"
#include "RigidBodyComponent.h"

namespace ecs {
    PushOutsideTriggerComponent::PushOutsideTriggerComponent(entity_t ent, float force) : PhysicsComponent(ent), _force(force)
    {
    }
    
    PushOutsideTriggerComponent::~PushOutsideTriggerComponent() {}

    void PushOutsideTriggerComponent::init(){
        _myRigidBody = _myEntity->getComponent<RigidBodyComponent>();
    } 

    void 
    PushOutsideTriggerComponent::onTriggerEnter(entity_t target) {
        if(target != _myEntity) {
            auto targetRb = target->getComponent<RigidBodyComponent>();
            b2Vec2 direction = targetRb->getPosition() - _myRigidBody->getPosition();
            direction = b2Normalize(direction);
            targetRb->applyForceToCenter(direction * _force);
        }
    }
}