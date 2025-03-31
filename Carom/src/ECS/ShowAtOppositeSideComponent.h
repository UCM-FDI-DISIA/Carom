#pragma once

#include "BallEffect.h"
#include <iostream>

namespace ecs{

    // ! debería ser physicsComponent o ballEffect?
    class ShowAtOppositeSideComponent : public PhysicsComponent{
    public:
    __CMPID_DECL__(ecs::cmp::SUBDIVISION_EFFECT)

        ShowAtOppositeSideComponent(ecs::entity_t ent) : PhysicsComponent(ent){}
        ~ShowAtOppositeSideComponent() {}
        
        void onCollisionEnter(entity_t collision) override;

    };
}