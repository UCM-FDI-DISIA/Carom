#pragma once

#include "CaromScene.h"

class PrefabTestScene: public CaromScene{
protected:
    void init() override;
public:
    PrefabTestScene(Game* g, std::shared_ptr<GameScene> reward);
};