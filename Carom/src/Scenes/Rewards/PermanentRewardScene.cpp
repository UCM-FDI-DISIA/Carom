#include "PermanentRewardScene.h"
#include "ScenesManager.h"
#include "PoolScene.h"
#include "InventoryManager.h"


PermanentRewardScene::PermanentRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
    , _name(_reward.getName())
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
    auto rng = RNG_Manager::Instance();
    auto inv = InventoryManager::Instance();

    if(_name == "cunning") {
        float value = rng->randomRange(0.05f,0.10f);
        inv->setCunning(inv->getCunning() - value);
    }
    else if(_name == "skill") {
        inv->setHitEase(inv->getHitEase() + 1);
    }
    else if(_name == "charisma") {
        float value = 2;
        inv->setCharisma(inv->getCharisma() + value);
    }
    else { // power
        auto inv = InventoryManager::Instance();
        inv->setPower(inv->getPower() + 1);
    }
}

void PermanentRewardScene::initObjects()
{
    
}

void PermanentRewardScene::initFunctionalities() 
{
    showExitButton();
}
