#pragma once

#include "RewardScene.h"
#include "PoolScene.h"
#include <vector>

class InventoryManager;

/// @brief Recompensa que le otorga al jugador todas las bolas del jefe
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
    bool checkIfBallIsObtained(int ballId);

    inline bool hasElement(std::vector<int>& vec, int elem) {
        return std::find(vec.begin(), vec.end(), elem) != vec.end();
    }

    std::vector<PoolScene::BallInfo> _obtainedBallsInfo;
    std::vector<int> _selectedBalls;
    InventoryManager* _inventory;
    std::vector<int> _ballsToRemove;
};