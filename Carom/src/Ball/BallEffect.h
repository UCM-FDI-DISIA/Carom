#pragma once
#include "Component.h"
#include "BallHandler.h"
#include "ecs.h"
#include <string>


class CaromScene;

class BallEffect : public Component
{
protected:
    std::string _name;
    std::string _description;
    BallHandler* _handler;
public:
    BallEffect(entity_t ent) : Component(ent) {}
    ~BallEffect() {}

    virtual void init() override;

    virtual void onHit(entity_t ent) {};
    virtual void onStrikeEnd() {};
    virtual void onBeingTargeted() {};
    virtual void onMultChanged() {};

    void render() override {}
    void handleEvent() override {}
    virtual void update() override {}
    virtual cmpId_t getEffectId() = 0;
};