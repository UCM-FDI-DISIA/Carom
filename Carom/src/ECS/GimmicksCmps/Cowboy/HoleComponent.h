#pragma once

#include "ForceAreaComponent.h"


using isInsideField = bool;

namespace ecs{

    // Component that captures a single body
    class HoleComponent : public ForceAreaComponent
    {
    protected:
        entity_t _nearBody;
        bool _isEmpty;
        float _maxVelocityToFall;
        float _maxDistToFall;
        
    public:
        __CMPID_DECL__(cmp::HOLE);

        HoleComponent(entity_t ent, b2Vec2 center, float magnitude);
        ~HoleComponent() {}

        virtual void onTriggerEnter(entity_t other) override;
        virtual void onTriggerExit(entity_t other) override; 
        b2Vec2 calculateForceToApply(entity_t e, Vector2D distanceVec, float other_vel);
        virtual void update() override;

        void resetChanges();
        void resetHole(const b2Vec2& pos);

    protected:
        virtual void applyForce(entity_t e) override;
        bool tryToCapture(RigidBodyComponent* other_rb, float centersDist);
    };

}
