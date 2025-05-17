#pragma once
#include "UIScene.h"

class AudioManager;
#include <memory>

class ScenesManager;
class MainMenuScene;

class ControlsScene: public UIScene 
{
protected:
    //AudioManager* _am;
    std::shared_ptr<MainMenuScene> _mainMenuScene;

public:
    ControlsScene(Game* g);
    virtual ~ControlsScene();

    void initObjects() override;
    void initFunctionalities() override;
};
