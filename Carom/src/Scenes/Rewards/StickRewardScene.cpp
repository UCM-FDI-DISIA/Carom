#include "StickRewardScene.h"

StickRewardScene::StickRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "STICK" << std::endl;
    #endif
}

StickRewardScene::~StickRewardScene()
{

}

void StickRewardScene::atRender()
{
    openInventory();
}

void StickRewardScene::applyReward()
{

}

void StickRewardScene::initObjects()
{

}

void StickRewardScene::initFunctionalities() 
{

}