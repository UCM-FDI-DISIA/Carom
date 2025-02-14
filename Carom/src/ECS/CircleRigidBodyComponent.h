#pragma once
#include "RigidBodyComponent.h"

namespace ecs{
    class CircleRigidBodyComponent : public RigidBodyComponent{
        
        CircleRigidBodyComponent(Entity* ent, b2BodyType type, float density, float friction, float restitution, float radius);
    };
}