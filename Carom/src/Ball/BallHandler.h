#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"
#include <vector>

namespace ecs{
class CaromScene;
class BallEffect;}

namespace ecs{
class BallHandler : public ecs::PhysicsComponent
{
private:
    std::vector<BallEffect*> _effects;
public:
    void init() override;
    void onCollisionEnter(ecs::entity_t collision) override;
    void onBeingTargeted();
    void onStrikeEnd();

    inline void addEffect(BallEffect* effect) {_effects.push_back(effect);}
    __CMPID_DECL__(ecs::cmp::BALL_HANDLER);
};}