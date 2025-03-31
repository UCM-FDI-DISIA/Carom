#pragma once

#include "BallEffect.h"
#include <iostream>

namespace ecs{

    // ! debería ser physicsComponent o ballEffect?
    class ShowAtOppositeSideComponent : public PhysicsComponent{
    public:
    __CMPID_DECL__(cmp::SUBDIVISION_EFFECT)

        ShowAtOppositeSideComponent(entity_t ent) : PhysicsComponent(ent){}
        ~ShowAtOppositeSideComponent() {}
        
        void onCollisionEnter(entity_t collision) override;

    };
}