#pragma once
#include "UIScene.h"

class AudioManager;
class ScenesManager;
class MainMenuScene: public UIScene {
    AudioManager* _am;
public:
    MainMenuScene(Game* g);
    virtual ~MainMenuScene() = default;
};
