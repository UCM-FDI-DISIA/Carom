#include "BossRewardScene.h"

BossRewardScene::BossRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "BOSS REWARD" << std::endl;
    #endif
}

BossRewardScene::~BossRewardScene()
{

}

void BossRewardScene::applyReward()
{
    
}

void BossRewardScene::initObjects()
{

}

void BossRewardScene::initFunctionalities() 
{

}