#include "GumballRewardScene.h"

GumballRewardScene::GumballRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "GUMBALL" << std::endl;
    #endif
}

GumballRewardScene::~GumballRewardScene()
{

}

void GumballRewardScene::applyReward()
{
    
}

void GumballRewardScene::initObjects()
{

}

void GumballRewardScene::initFunctionalities() 
{

}