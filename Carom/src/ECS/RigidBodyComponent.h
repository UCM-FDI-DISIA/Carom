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

        static enum bodyType {
            STATIC,
            DYNAMIC,
            KINEMATIC
        };

        RigidBodyComponent(Entity*, b2WorldId, TransformComponent*, bodyType);
        ~RigidBodyComponent() {}


    };
}