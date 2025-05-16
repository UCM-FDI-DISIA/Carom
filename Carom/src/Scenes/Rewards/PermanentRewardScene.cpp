#include "PermanentRewardScene.h"

PermanentRewardScene::PermanentRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "PERMANENT" << std::endl;
    #endif
}

PermanentRewardScene::~PermanentRewardScene()
{

}

void PermanentRewardScene::applyReward()
{
    
}

void PermanentRewardScene::initObjects()
{

}

void PermanentRewardScene::initFunctionalities() 
{

}