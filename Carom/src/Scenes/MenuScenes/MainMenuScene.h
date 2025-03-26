#pragma once
#include "UIScene.h"
namespace ecs{
    class ScenesManager;
    class MainMenuScene: public UIScene {
    public:
        MainMenuScene(State* s, Game* g);
        virtual ~MainMenuScene() = default;
    };
}