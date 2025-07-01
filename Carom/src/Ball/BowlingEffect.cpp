#include "BowlingEffect.h"
#include "RigidBodyComponent.h"
#include "Entity.h"

//Se ejecuta al añadir el efecto a la bola, cambia la densidad y la fricción del rigidbody
void BowlingEffect::updateEffect()
{
    assert(_handler->_myEntity->tryGetComponent<RigidBodyComponent>() && "Se está intentando añadir el componente BowlingEffect a una entidad sin rigibody");

    RigidBodyComponent* rb =_handler->_myEntity->getComponent<RigidBodyComponent>();
    rb->setDensity(DENSITY * _handler->getMult());
    rb->setFriction(FRICTION * _handler->getMult());
}

//Cuando cambia el multiplicador del handler se actualiza el efecto
void BowlingEffect::onMultChanged()
{
    updateEffect();
}