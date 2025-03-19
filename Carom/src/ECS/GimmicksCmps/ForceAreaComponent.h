#pragma once

#include <box2d/box2d.h>
#include "Vector2D.h"

#include "PhysicsComponent.h"
#include "ForceFieldComponent.h"


namespace ecs{

    // Component that defines the force of the field: magitude and if its attractive or repulsive.
    // By default the force has the direction from the center of the other body to the center of this body
    // This class can be inherit to override and costumize force definition and conditions to apply force
    class ForceAreaComponent : public ForceFieldComponent
    {
    protected:
        b2Vec2 _myCenter;
        float _minMagnitude;
        bool _attraction;
        float _maxVelToTrigger; // above this the body ignores the force

    public:
        __CMPID_DECL__(cmp::FORCE_AREA);
        
        // If attraction is false the force is repulsion
        ForceAreaComponent(entity_t ent, b2Vec2 center, float magnitude, bool attraction = true);
        virtual ~ForceAreaComponent() {}
    
    protected:
        virtual void defineForce(entity_t e);
        virtual void applyForce(entity_t e) = 0;
    };

}