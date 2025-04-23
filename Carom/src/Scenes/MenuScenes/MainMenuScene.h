#pragma once
#include "UIScene.h"

#include <memory>

class ScenesManager;
class PoolScene;

class MainMenuScene: public UIScene 
{
protected:
    std::shared_ptr<PoolScene> _poolScene;

public:
    MainMenuScene(Game* g);
    virtual ~MainMenuScene();

    void initObjects() override;
    void initFunctionalities() override;
};
