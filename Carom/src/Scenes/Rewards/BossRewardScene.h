#pragma once

#include "RewardScene.h"
#include "PoolScene.h"
#include <vector>

class InventoryManager;

class BossRewardScene : public RewardScene 
{    
public:
    BossRewardScene(Game* game, Reward reward);
    virtual ~BossRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;

private:
    void checkIfValid();

    bool checkIfBallIsSelected(int ballId);
    bool checkIfBallIsObtained(PoolScene::BallInfo ballInfo);

    std::vector<PoolScene::BallInfo> _obtainedBallsInfo;
    std::vector<PoolScene::BallInfo> _selectedBalls;
    InventoryManager* _inventory;
    std::vector<int> _ballsToRemove;
};