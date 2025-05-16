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

void FusionRewardScene::atRender()
{
    openInventory();
    // TODO: meter onclick de los botones de las bolas con la movida
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