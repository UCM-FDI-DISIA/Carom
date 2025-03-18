#pragma once

#include <box2d/box2d.h>
#include "Vector2D.h"

#include "PhysicsComponent.h"
#include "ForceFieldComponent.h"


namespace ecs{

    class ForceAreaComponent : public ForceFieldComponent
    {
    protected:
        b2Vec2 _myCenter;
        b2Vec2 _force;
        float _minMagnitude;
        bool _attraction;
        float _maxVelToTrigger; // above this the body ignores the force

    public:
        __CMPID_DECL__(cmp::FORCE_AREA);
        
        // If attraction is false the force is repulsion
        ForceAreaComponent(entity_t ent, b2Vec2 center, float magnitude, bool attraction);
    
    protected:
        void defineForce(entity_t e);
        virtual void applyForce(entity_t e, b2Vec2 force) override;
    };

}