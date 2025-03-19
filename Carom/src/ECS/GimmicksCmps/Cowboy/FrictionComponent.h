#pragma once

#include "ForceFieldComponent.h"


namespace ecs{

    // Component to be added to an entity with RB set to sensor
    // Objects inside recieve a counter force during motion
    // It doesn't use linearDamping for 2 reasons:
    // - Avoiding conflict with stick ability
    // - Reuse logic to force field like components
    class FrictionComponent : public ForceFieldComponent
    { 
        float _mu; // friction coeficient (no distinction dynamic/static)
        const float _g = 9.8f; // """"gravity""""
        
    public:
        __CMPID_DECL__(cmp::FRICTION);
        
        FrictionComponent(entity_t ent, float frictionCoef = 2);
        virtual ~FrictionComponent() {}
        
    protected:
        virtual void applyForce(entity_t e) override;

    };

}