 #include "RewardScene.h"

RewardScene::RewardScene(Game* game, Reward reward) : UIScene(game), _reward(reward) 
{
}

RewardScene::~RewardScene() {

}

void 
RewardScene::init() 
{
    createBackground("suelo");
    createTable();

    initObjects();
    initFunctionalities();
    applyReward();
}

void 
RewardScene::initObjects() 
{
}

void 
RewardScene::showContinue() 
{
    //Activar el botón
}