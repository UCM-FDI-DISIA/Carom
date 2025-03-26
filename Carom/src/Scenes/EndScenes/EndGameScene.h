#pragma once
#include "UIScene.h"
#include "MainMenuScene.h"
namespace ecs{
    class ScenesManager;
    class EndGameScene: public UIScene {  
    public:
        EndGameScene(Game* g); // para cuando se pierde.
        virtual ~EndGameScene() = default;
    };
}