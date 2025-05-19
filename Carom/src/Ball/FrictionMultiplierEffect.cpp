#include "FrictionMultiplierEffect.h"
#include "RigidBodyComponent.h"
#include "Entity.h"


FrictionMultiplierEffect::FrictionMultiplierEffect(entity_t entity, float friction) : BallEffect(entity), _frictionFactor(friction)
{

}

FrictionMultiplierEffect::~FrictionMultiplierEffect(){}

void FrictionMultiplierEffect::init() {
    _rigidBody = _myEntity->getComponent<RigidBodyComponent>();
    assert(_rigidBody != nullptr);

    _rigidBody->setLinearDamping(_rigidBody->getLinearDamping() * _frictionFactor);
}

void FrictionMultiplierEffect::onStrikeEnd() {
    _rigidBody->setLinearDamping(_rigidBody->getLinearDamping() / _frictionFactor);
    _myEntity->removeComponent<FrictionMultiplierEffect>();
}
