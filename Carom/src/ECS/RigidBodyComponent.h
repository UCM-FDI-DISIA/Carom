#pragma once
#include "PhysicsComponent.h"
#include <box2D/box2D.h>

class TransformComponent;

namespace ecs{
    class RigidBodyComponent : public PhysicsComponent
    {
        b2BodyId _body; //Cuerpo como tal
        b2Transform _b2Transform;
        TransformComponent* _transform;

        public:

        RigidBodyComponent(Entity*, b2BodyId, TransformComponent*);

        inline b2Transform* getB2Transform(){return &_b2Transform;}
        inline b2BodyId* getB2Body(){return &_body;}

        void updateB2Transform(); //Facilita las conversiones al cambiar los updates
        void changeBodyType();
    };
}