#include "CauldronRewardScene.h"

CauldronRewardScene::CauldronRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "CAULDRON" << std::endl;
    #endif
}

CauldronRewardScene::~CauldronRewardScene()
{

}

void CauldronRewardScene::applyReward()
{
    
}

void CauldronRewardScene::initObjects()
{

}

void CauldronRewardScene::initFunctionalities() 
{

}