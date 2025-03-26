#pragma once
#include "InfoComponent.h"
#include "BallHandler.h"
#include "ecs.h"
#include <string>

class CaromScene;

class BallEffect : public InfoComponent
{
protected:
    std::string _name;
    std::string _description;
    BallHandler* _handler;
public:
    BallEffect(entity_t ent) : InfoComponent(ent) {}
    ~BallEffect() {}

    virtual void init() override;

    virtual void onHit(entity_t ent) {};
    virtual void onStrikeEnd() {};
    virtual void onBeingTargeted() {};
    virtual void onMultChanged() {};

    virtual cmpId_t getEffectId() = 0;
};