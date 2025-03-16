#include <Vector2D.h>

#include "Entity.h"
#include "GameScene.h"
#include "FrictionComponent.h"
#include "WhiteBallScorerComponent.h"


namespace ecs{

    FrictionComponent::FrictionComponent(entity_t ent, float frictionCoef)
        : ForceFieldComponent(ent), _mu(frictionCoef)
    {
    }

    void FrictionComponent::applyForce(entity_t e)
    {
        auto rb = e->getComponent<RigidBodyComponent>();

        if(bodyIsMoving(*rb)){

            float    a_bodyMass = rb->getMass();
            Vector2D a_bodyVel = {rb->getVelocity().x, rb->getVelocity().y};
            Vector2D a_frictionForce = a_bodyVel.normalize() * (-1) * _mu * a_bodyMass * _g;
            rb->applyForceToCenter({a_frictionForce.getX(), a_frictionForce.getY()});

            if (e->tryGetComponent<WhiteBallScorerComponent>()){
                // TODO: camera shake
            }
        }
    }

}
