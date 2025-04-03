#pragma once

#include "CaromScene.h"

class PrefabTestScene: public CaromScene{
protected:
    void init() override;
public:
    PrefabTestScene(State* state, Game* g, GameScene* reward);
};