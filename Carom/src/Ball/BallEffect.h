#pragma once
#include "InfoComponent.h"
#include "BallHandler.h"
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
    BallHandler* _handler;
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