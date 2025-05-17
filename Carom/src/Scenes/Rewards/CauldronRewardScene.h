#pragma once

#include "RewardScene.h"
#include "BallInfoDisplayComponent.h"

class CauldronRewardScene : public RewardScene 
{
    friend class Entity;

    RewardScene::ballID _randomEffect;
    int _selectedBallId;

public:
    CauldronRewardScene(Game* game, Reward reward);
    virtual ~CauldronRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};