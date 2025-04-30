#pragma once
#include "UIScene.h"

class AudioManager;
class ScenesManager;
class MainMenuScene: public UIScene {
    AudioManager* am;
public:
    MainMenuScene(Game* g);
    virtual ~MainMenuScene() = default;
};
