#pragma once
#include "PhysicsComponent.h"
#include <box2D/box2D.h>

class TransformComponent;

namespace ecs{
    class RigidBodyComponent : public PhysicsComponent
    {
        b2BodyId _body; //Cuerpo como tal
        TransformComponent* _transform;

        public:

        enum shape{
            CIRCLE,
            POLYGON,
            CAPSULE
        };

        RigidBodyComponent(Entity*, b2BodyId, shape);

        inline b2Transform* getB2Transform(){return &b2Body_GetTransform(_body);}
        inline b2BodyId* getB2Body(){return &_body;}

        void updateB2Transform(); //Facilita las conversiones al cambiar los updates
        void changeBodyType();
    };

}