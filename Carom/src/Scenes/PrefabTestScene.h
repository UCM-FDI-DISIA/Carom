#pragma once

#include "GameScene.h"

class PrefabTestScene: public ecs::GameScene{
protected:
    void init() override;
public:
    PrefabTestScene(Game* game);
};