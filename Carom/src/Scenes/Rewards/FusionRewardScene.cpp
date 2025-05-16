#include "FusionRewardScene.h"

FusionRewardScene::FusionRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "FUSION" << std::endl;
    #endif
}

FusionRewardScene::~FusionRewardScene()
{

}

void FusionRewardScene::applyReward()
{
    
}

void FusionRewardScene::initObjects()
{

}

void FusionRewardScene::initFunctionalities() 
{

}