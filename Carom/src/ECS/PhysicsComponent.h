#pragma once
#include "Component.h"
#include "ecs.h"
#include <functional>

class Camera;
// * Heredar de esta clase para implementar onCollision y onTrigger

class PhysicsComponent : public Component{
private:
    std::function<void()> _onDestroy;

public:
    PhysicsComponent(entity_t ent);
    ~PhysicsComponent();

    inline virtual void init() override {}
    inline virtual void handleEvent() override {}
    inline virtual void update() override {}
    inline virtual void render(Camera*) override {}

    virtual void onCollisionEnter(entity_t collision) {}
    virtual void onCollisionExit(entity_t collision) {}

    virtual void onTriggerEnter(entity_t target) {}
    virtual void onTriggerExit(entity_t target) {}

    inline void setOnDestroy(std::function<void()> f) {_onDestroy = f;}
};