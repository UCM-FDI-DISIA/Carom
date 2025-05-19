#include <Vector2D.h>

#include "Entity.h"
#include "GameScene.h"
#include "FrictionComponent.h"
#include "WhiteBallScorerComponent.h"


FrictionComponent::FrictionComponent(entity_t ent, float frictionCoef)
    : ForceFieldComponent(ent), _mu(frictionCoef)
{
    // Max friction force applied
    _maxForce = 2.0f;
}

void FrictionComponent::applyForce(RigidBodyComponent* rb)
{
    if(bodyIsMoving(*rb) && rb->getBodyType() == b2_dynamicBody) {
        
        calculateMyForceVector(rb, Vector2D());
        rb->applyForceToCenter({_myForce.x, _myForce.y});
    }
}

void
FrictionComponent::calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction)
{
    float    a_bodyMass = rb->getMass();
    Vector2D a_bodyVel = {rb->getVelocity().x, rb->getVelocity().y};
    float    a_mag = (_mu * a_bodyMass * _g) * a_bodyVel.magnitude();

    // Friction magnitude capped by _maxForce
    Vector2D a_frictionForce = a_bodyVel.normalize() * (-1) * b2ClampFloat(a_mag, 0, _maxForce);

    _myForce = {a_frictionForce.getX(), a_frictionForce.getY()};
}
