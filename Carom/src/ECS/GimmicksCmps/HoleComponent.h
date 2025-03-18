#pragma once

#include "ForceAreaComponent.h"


using isInsideField = bool;

namespace ecs{

    //
    class HoleComponent : public ForceAreaComponent
    {
    protected:
        entity_t _bodyCaptured;
        float _minVelocityToFall;
        float _maxDistToFall;
        
    public:
        __CMPID_DECL__(cmp::HOLE);

        HoleComponent(entity_t ent, b2Vec2 center, float magnitude);
        ~HoleComponent() {}

        virtual void onTriggerEnter(entity_t other) override;
        virtual void onTriggerExit(entity_t other) override; 
        b2Vec2 calculateForceToApply(entity_t e, Vector2D distanceVec, float other_vel);
        virtual void applyForce(entity_t e, b2Vec2 force) override;
        bool tryToCapture(RigidBodyComponent* other_rb, float centersDist);
        virtual void update() override;
    };

}
