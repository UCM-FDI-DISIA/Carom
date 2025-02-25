#pragma once
#include "Component.h"
#include "ecs.h"

class Camera;
// * Heredar de esta clase para implementar onCollision y onTrigger
namespace ecs{

    class PhysicsComponent : public Component{
    public:
        PhysicsComponent(entity_t ent);
        inline virtual void init() override {}
        inline virtual void handleEvent() override {}
        inline virtual void update() override {}
        inline virtual void render(Camera*) override {}

        virtual void onCollisionEnter(entity_t collision) {}
        virtual void onCollisionExit(entity_t collision) {}

        virtual void onTriggerEnter(entity_t target) {}
        virtual void onTriggerExit(entity_t target) {}
    };
}