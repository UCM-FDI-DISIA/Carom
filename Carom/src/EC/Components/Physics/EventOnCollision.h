#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"
#include <vector>
#include <functional>


class EventOnCollision : public PhysicsComponent{
    private:
    std::function<void(entity_t, b2Manifold&)> _onCollisionEnter;
    std::function<void(entity_t)> _onCollisionExit;

    public:
    __CMPID_DECL__(cmp::EVENT_ON_COLLISION);

    EventOnCollision(entity_t ent);
    EventOnCollision(entity_t ent, std::function<void(entity_t, b2Manifold&)> enter, std::function<void(entity_t)> exit);

    void onCollisionEnter(entity_t other, b2Manifold& contactData) override;
    void onCollisionExit(entity_t other) override;
};