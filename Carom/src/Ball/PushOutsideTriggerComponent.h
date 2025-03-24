#pragma once 

#include "PhysicsComponent.h"

namespace ecs {
    class RigidBodyComponent;
    class PushOutsideTriggerComponent : public PhysicsComponent {
        float _force;
        entity_t _inmune;
        RigidBodyComponent* _myRigidBody;
    public:

        __CMPID_DECL__(cmp::PUSH_OUTSIDE_TRIGGER);
        ecs::cmpId_t getEffectId() {return ecs::cmp::PUSH_OUTSIDE_TRIGGER;};

        PushOutsideTriggerComponent(entity_t ent, float force, entity_t inmuneEnt = nullptr);
        ~PushOutsideTriggerComponent();

        void init() override;
        virtual void onTriggerEnter(entity_t target); 
    };
}