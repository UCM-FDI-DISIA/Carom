#pragma once

#include "RewardScene.h"

class FusionRewardScene : public RewardScene 
{    
public:
    FusionRewardScene(Game* game, Reward reward);
    virtual ~FusionRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};