
#pragma once

#include "RewardScene.h"

class PermanentRewardScene : public RewardScene 
{    
public:
    PermanentRewardScene(Game* game, Reward reward);
    virtual ~PermanentRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};