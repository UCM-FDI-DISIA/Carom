#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"
#include <vector>
class CaromScene;
class BallEffect;

class BallHandler : public ecs::PhysicsComponent
{
private:
    std::vector<BallEffect*> _effects;
public:
    void init() override;
    void onCollisionEnter(ecs::entity_t collision) override;
    void onStrikeEnd();

    inline void addEffect(BallEffect* effect) {_effects.push_back(effect);}
};