#pragma once
#include "UIScene.h"

namespace ecs{
    class ScenesManager;
    class MainMenuScene: public UIScene {
    public:
        MainMenuScene(Game* g);
        virtual ~MainMenuScene() = default;
    };
}