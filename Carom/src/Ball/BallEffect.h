#pragma once
#include "InfoComponent.h"
#include <string>
class CaromScene;

class BallEffect : public ecs::InfoComponent
{
protected:
    std::string _name;
    std::string _description;
    ecs::CaromScene* _scene;
public:
    void init() override;
    void onHit(ecs::entity_t ent) {};
    void onStrikeEnd() {};
};