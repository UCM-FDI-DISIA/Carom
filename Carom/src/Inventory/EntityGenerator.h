#pragma once

#include "ecs.h"
#include <vector>
#include <box2d/box2d.h>

class GameScene;
class EntityGenerator{
public:
    static std::vector<entity_t> generateInventoryBalls(GameScene& s, std::vector<b2Vec2> pos);
    static entity_t generateInventoryStick(GameScene& s, b2Vec2 pos);

    static entity_t generateBall(GameScene& s, std::vector<effectId_t> effects, b2Vec2 pos, grpId_t group);
    static entity_t generateWhiteBall(GameScene& s, b2Vec2 pos);
};