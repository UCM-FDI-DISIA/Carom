
#pragma once

#include "RewardScene.h"

class PermanentRewardScene : public RewardScene 
{    
public:
    PermanentRewardScene(Game* game, Reward reward);
    virtual ~PermanentRewardScene();

    void applyReward() override;
    void initObjects() override; 
    void initFunctionalities() override;

private:
    std::string _name;
};