#include "ForceAreaComponent.h"

#include "Entity.h"
#include "RigidBodyComponent.h"
#include "WhiteBallScorerComponent.h"


ecs::ForceAreaComponent::ForceAreaComponent(entity_t ent, float magnitude, bool attraction)
    : ForceFieldComponent(ent), _minMagnitude(magnitude), _attraction(attraction)
{
}

void ecs::ForceAreaComponent::defineForce(entity_t e)
{
    auto rb = e->getComponent<RigidBodyComponent>();

    Vector2D a_bodyPos = {rb->getPosition().x, rb->getPosition().y};
    Vector2D a_myCenter = {_myCenter.x, _myCenter.y};

    // When the force is attraction:
    Vector2D a_fieldForceVec = (a_myCenter - a_bodyPos);
    if(!_attraction)
        a_fieldForceVec = a_fieldForceVec * (-1);

    float a_dist = a_fieldForceVec.magnitude();
    float a_magnitude = _minMagnitude;
    // TODO: mejorar función
    Vector2D a_force = a_fieldForceVec.normalize() * a_magnitude * a_dist;
    _myForce = {a_force.getX(), a_force.getY()};
}

void ecs::ForceAreaComponent::applyForce(entity_t e)
{
    auto rb = e->getComponent<RigidBodyComponent>();

    if(bodyIsMoving(*rb)){

        rb->applyForceToCenter(_myForce);

        if (e->tryGetComponent<WhiteBallScorerComponent>()){
            // TODO: camera shake ??
        }
    }
}

void ecs::ForceAreaComponent::defineCenter(b2Vec2 c){
    _myCenter = c;
}

