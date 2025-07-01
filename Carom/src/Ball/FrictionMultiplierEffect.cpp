#include "FrictionMultiplierEffect.h"
#include "RigidBodyComponent.h"
#include "Entity.h"


FrictionMultiplierEffect::FrictionMultiplierEffect(BallHandler* hndlr, float friction) : BallEffect(hndlr), _frictionFactor(friction)
{

}

FrictionMultiplierEffect::~FrictionMultiplierEffect(){}

void FrictionMultiplierEffect::init() {
    _rigidBody = _handler->_myEntity->getComponent<RigidBodyComponent>();
    assert(_rigidBody != nullptr);

    _rigidBody->setLinearDamping(_rigidBody->getLinearDamping() * _frictionFactor);
}

void FrictionMultiplierEffect::onStrikeEnd() {
    _rigidBody->setLinearDamping(_rigidBody->getLinearDamping() / _frictionFactor);
    _handler->_myEntity->removeComponent<FrictionMultiplierEffect>();
}
