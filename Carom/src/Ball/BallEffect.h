#pragma once
#include "Component.h"
#include "ecs.h"
#include <string>

namespace ecs
{class CaromScene;}

namespace ecs{
class BallEffect : public ecs::Component
{
protected:
    std::string _name;
    std::string _description;
    ecs::CaromScene* _scene;
public:
    BallEffect(ecs::entity_t ent) : Component(ent) {}
    ~BallEffect() {}

    virtual void init() override;
    virtual void onHit(ecs::entity_t ent) {};
    virtual void onStrikeEnd() {};
    virtual void onBeingTargeted() {};

    void render(Camera*) override {}
    void handleEvent() override {}
    virtual void update() override {}

    __CMPID_DECL__(ecs::cmp::BALL_EFFECT);
};}