
#pragma once

#include "RewardScene.h"

class GumballRewardScene : public RewardScene 
{    
public:
    GumballRewardScene(Game* game, Reward reward);
    virtual ~GumballRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};