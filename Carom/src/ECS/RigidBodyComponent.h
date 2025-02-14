#pragma once
#include "PhysicsComponent.h"
#include <box2D/box2D.h>

class TransformComponent;
class B2Manager;

namespace ecs{
    class RigidBodyComponent : public PhysicsComponent
    {
        b2BodyId _body; // b2 Body ID
        TransformComponent* _transform; // Our transform component
        B2Manager* _manager; // Physics Manager Singleton

        public:

        RigidBodyComponent(Entity* ent);
        virtual ~RigidBodyComponent(){}

        inline b2Transform* getB2Transform(){return &b2Body_GetTransform(_body);}
        inline b2BodyId* getB2Body(){return &_body;}
    };

}