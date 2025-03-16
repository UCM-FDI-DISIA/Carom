#pragma once
#include <box2d/box2d.h>
#include "Vector2D.h"
#include "ecs.h"

#include "PhysicsComponent.h"
#include "ForceFieldComponent.h"


namespace ecs{

    class ForceAreaComponent : public ForceFieldComponent
    { 
        Vector2D _myCenter;
        float _minMagnitude;

    public:
        __CMPID_DECL__(cmp::FORCE_AREA);
        
        ForceAreaComponent(entity_t ent, b2Vec2 center, float magnitude);
    
    protected:
        virtual void applyForce(entity_t e) override;
    };

}