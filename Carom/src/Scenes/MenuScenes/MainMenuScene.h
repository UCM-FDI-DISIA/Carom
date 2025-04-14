#pragma once
#include "UIScene.h"


class ScenesManager;
class PoolScene;

class MainMenuScene: public UIScene 
{
protected:
    PoolScene* _poolScene;

public:
    MainMenuScene(Game* g);
    virtual ~MainMenuScene();

    void initObjects() override;
    void initFunctionalities() override;
};
