#pragma once
#include "InfoComponent.h"
#include "ecs.h"
#include <string>

namespace ecs
{class CaromScene;}

class BallEffect : public ecs::InfoComponent
{
protected:
    std::string _name;
    std::string _description;
    ecs::CaromScene* _scene;
public:
    void init() override;
    virtual void onHit(ecs::entity_t ent) {};
    virtual void onStrikeEnd() {};
    virtual void onBeingTargeted() {};

    __CMPID_DECL__(ecs::cmp::BALL_EFFECT);
};