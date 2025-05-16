#pragma once

#include "RewardScene.h"

class BossRewardScene : public RewardScene 
{    
public:
    BossRewardScene(Game* game, Reward reward);
    virtual ~BossRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};