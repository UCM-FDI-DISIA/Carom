#pragma once
#include "PhysicsComponent.h"
#include <box2D/box2D.h>

class TransformComponent;
class B2Manager;

namespace ecs{
    class RigidBodyComponent : public PhysicsComponent
    {
        b2BodyId _body; //Cuerpo como tal
        TransformComponent* _transform;
        B2Manager* _manager;

        public:

        enum shape{
            CIRCLE,
            POLYGON,
            CAPSULE
        };

        RigidBodyComponent(Entity*, b2BodyId, float, float, float, shape, float);

        inline b2Transform* getB2Transform(){return &b2Body_GetTransform(_body);}
        inline b2BodyId* getB2Body(){return &_body;}

        void updateB2Transform(); //Facilita las conversiones al cambiar los updates
        void changeBodyType();
    };

}