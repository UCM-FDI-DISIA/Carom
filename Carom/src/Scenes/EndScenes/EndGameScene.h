#pragma once
#include "EndScene.h"

namespace ecs{
    class ScenesManager;
    class EndGameScene: public EndScene {  
    public:
        EndGameScene(Game* g); // para cuando se pierde.
        virtual ~EndGameScene() = default;
    };

}