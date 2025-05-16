 #include "RewardScene.h"

RewardScene::RewardScene(Game* game, Reward reward) : UIScene(game), _reward(reward) 
{
}

RewardScene::~RewardScene() {

}

void 
RewardScene::init() {
    initObjects();
    initFunctionalities();
    applyReward();
}

void 
RewardScene::initObjects() {
    //Crear botón de continuar y el cajón 
}

void 
RewardScene::showContinue() {
    //Activar el botón
}