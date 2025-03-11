#pragma once

#include "CaromScene.h"

namespace ecs{
    class CowboyPoolScene : public ecs::CaromScene{
        void initGimmick();

public:
        CowboyPoolScene(State* state, Game* g, GameScene* reward);
        
    };
}
