#pragma once

#include "CaromScene.h"

class PrefabTestScene: public ecs::CaromScene{
protected:
    void init() override;
public:
    PrefabTestScene(State* state, Game* g, GameScene* reward);
};