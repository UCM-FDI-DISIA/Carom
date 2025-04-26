#include "BowlingEffect.h"
#include "RigidBodyComponent.h"
#include "Entity.h"

void BowlingEffect::init()
{
    BallEffect::init();
    updateEffect();
}

void BowlingEffect::updateEffect()
{
    assert(_myEntity->tryGetComponent<RigidBodyComponent>() && "Se está intentando añadir el componente BowlingEffect a una entidad sin rigibody");

    RigidBodyComponent* rb =_myEntity->getComponent<RigidBodyComponent>();
    rb->setDensity(DENSITY * _handler->getMult());
    rb->setFriction(FRICTION * _handler->getMult());
}

void BowlingEffect::onMultChanged()
{
    updateEffect();
}