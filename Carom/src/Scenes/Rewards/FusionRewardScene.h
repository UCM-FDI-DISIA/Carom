#pragma once

#include "InstantRewardScene.h"

class FusionRewardScene : public InstantRewardScene 
{    
public:
    FusionRewardScene(Game* game, Reward reward);
    virtual ~FusionRewardScene();

    void atRender() override;

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;

    bool isSelected(int index);
};