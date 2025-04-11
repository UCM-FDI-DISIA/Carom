#include "PyramidComponent.h"


PyramidComponent::PyramidComponent(entity_t ent, const b2Vec2& direction, float slope)
    : ForceFieldComponent(ent)
    , _direction(direction)
    , _slope(slope)
{
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
    float a_mag = rb->getMass() * _g * cos(_slope);
    _myForce = {direction.normalize().getX() * a_mag, direction.normalize().getY() * a_mag};
}
