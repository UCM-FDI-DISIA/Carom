#pragma once

#include "RewardScene.h"

class StickRewardScene : public RewardScene 
{    
public:
    StickRewardScene(Game* game, Reward reward);
    virtual ~StickRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};