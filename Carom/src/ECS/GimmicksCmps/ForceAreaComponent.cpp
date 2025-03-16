#include "ForceAreaComponent.h"

#include "Entity.h"
#include "RigidBodyComponent.h"
#include "WhiteBallScorerComponent.h"


ecs::ForceAreaComponent::ForceAreaComponent(entity_t ent, b2Vec2 center, float magnitude)
    : ForceFieldComponent(ent), _minMagnitude(magnitude)
{
}

void ecs::ForceAreaComponent::applyForce(entity_t e)
{
    auto rb = e->getComponent<RigidBodyComponent>();

    if(bodyIsMoving(*rb)){

        Vector2D a_bodyPos = {rb->getPosition().x, rb->getPosition().y};

        Vector2D a_fieldForceVec = (_myCenter - a_bodyPos);
        float a_dist = a_fieldForceVec.magnitude();
        float a_magnitude = _minMagnitude;
        Vector2D a_force = a_fieldForceVec.normalize() * a_magnitude * a_dist;

        //  ! if the ball is some small distance from the center set velocity to 0 ??

        rb->applyForceToCenter({a_force.getX(), a_force.getY()});

        if (e->tryGetComponent<WhiteBallScorerComponent>()){
            // TODO: camera shake ??
        }
    }
}
