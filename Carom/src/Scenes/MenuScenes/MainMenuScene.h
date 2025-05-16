#pragma once
#include "UIScene.h"

class AudioManager;
#include <memory>

class ScenesManager;
class PoolScene;

class MainMenuScene: public UIScene 
{
protected:
    AudioManager* _am;

public:
    MainMenuScene(Game* g);
    virtual ~MainMenuScene();

    void initObjects() override;
    void initFunctionalities() override;
};
