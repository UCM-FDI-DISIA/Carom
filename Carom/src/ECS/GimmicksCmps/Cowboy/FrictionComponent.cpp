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

void FrictionComponent::applyForce(entity_t e)
{
    auto rb = e->getComponent<RigidBodyComponent>();

    if(bodyIsMoving(*rb) && rb->getBodyType() == b2_dynamicBody){

        float    a_bodyMass = rb->getMass();
        Vector2D a_bodyVel = {rb->getVelocity().x, rb->getVelocity().y};
        float a_mag = (_mu * a_bodyMass * _g) * a_bodyVel.magnitude();

        // Friction magnitude capped by _maxForce
        Vector2D a_frictionForce = a_bodyVel.normalize() * (-1) * b2ClampFloat(a_mag, 0, _maxForce);
        
        rb->applyForceToCenter({a_frictionForce.getX(), a_frictionForce.getY()});

        if (e->tryGetComponent<WhiteBallScorerComponent>()){
            // TODO:
            // _myEntity->getScene().getCamera()->shakeCamera(0.15f, 0.3f);
        }
    }
}
