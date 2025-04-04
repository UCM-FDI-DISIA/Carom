#pragma once
#include "UIScene.h"


class ScenesManager;
class MainMenuScene: public UIScene {
public:
    MainMenuScene(Game* g);
    virtual ~MainMenuScene() = default;
};
