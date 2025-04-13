#include "PyramidComponent.h"
// #include <iostream>


PyramidComponent::PyramidComponent(entity_t ent, const b2Vec2& direction, float slope)
    : ForceFieldComponent(ent)
    , _direction(direction)
    , _slope(slope)
{
    // Tunning:
    _minForce = 0.018f; // float a_mag = rb->getMass() * _g * sin(M_PI/3.0);
    _maxForce = 0.09f;
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
    float a_mag     = b2ClampFloat(velFactor, _minForce, _maxForce);

    // std::cout << "FORCE MAG: " << a_mag << std::endl;
    _myForce = {direction.normalize().getX() * a_mag, direction.normalize().getY() * a_mag};
}
