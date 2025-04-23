#include "PyramidComponent.h"
#include <iostream>


PyramidComponent::PyramidComponent(entity_t ent, const b2Vec2& direction, float slope)
    : ForceFieldComponent(ent)
    , _direction(direction)
    , _slope(slope)
{
    // Tunning:
    _minForce = 0.018f; // float a_mag = rb->getMass() * _g * sin(M_PI/3.0);
    _maxForce = 0.200f;

    _maxVelocity = 3.0f;
}


void 
PyramidComponent::applyForce(RigidBodyComponent* rb)
{
    calculateMyForceVector(rb, {_direction.x, _direction.y});
    rb->applyForceToCenter({_myForce.x, _myForce.y});
}

void
PyramidComponent::calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction)
{
    float coef      = 3;
    float vel       = rb->getVelocityMag();
    float velFactor = _minForce * pow(coef, vel);
    float a_mag;

    b2Vec2 bodyVel = rb->getVelocity();
    b2Vec2 forceDirection = {direction.normalize().getX(), direction.normalize().getY()};

    float dotProduct = bodyVel.x * forceDirection.x + bodyVel.y * forceDirection.y;

    if (dotProduct < 0 && vel > _maxVelocity)
        a_mag = b2ClampFloat(velFactor, _minForce, _maxForce);
    else
        a_mag = rb->getMass() * _g * cos(M_PI/3.0);

    _myForce = {forceDirection.x * a_mag, forceDirection.y * a_mag};
}
