#pragma once

#include "RewardScene.h"

class CauldronRewardScene : public RewardScene 
{    
public:
    CauldronRewardScene(Game* game, Reward reward);
    virtual ~CauldronRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};