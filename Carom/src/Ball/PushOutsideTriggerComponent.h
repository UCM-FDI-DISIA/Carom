#pragma once 

#include "PhysicsComponent.h"

namespace ecs {
    class RigidBodyComponent;
    class PushOutsideTriggerComponent : public PhysicsComponent {
        float _force;
        RigidBodyComponent* _myRigidBody;
    public:

        __CMPID_DECL__(cmp::PUSH_OUTSIDE_TRIGGER);
        ecs::cmpId_t getEffectId() {return ecs::cmp::PUSH_OUTSIDE_TRIGGER;};

        PushOutsideTriggerComponent(entity_t ent, float force);
        ~PushOutsideTriggerComponent();

        void init() override;
        virtual void onTriggerEnter(entity_t target); 
    };
}