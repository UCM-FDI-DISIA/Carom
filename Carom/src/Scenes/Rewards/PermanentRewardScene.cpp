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

    if(_name == Reward::CUNNING) {
        float value = rng->randomRange(0.05f,0.10f);
        inv->setCunning(inv->getCunning() - value);
    }
    else if(_name == Reward::SKILL) {
        std::vector<RandomItem<std::string_view>> a_skillTypes = {
            {Reward::SKILL_CARAMBOLA, 1.0},
            {Reward::SKILL_GOLPE, 1.0},
            {Reward::SKILL_COMBO, 1.0}
        };

        std::string_view a_selectedSkill = rng->getRandomItem(a_skillTypes, false);

        if (a_selectedSkill == Reward::SKILL_CARAMBOLA) {
            inv->setCaromEase(inv->getCaromEase() + 1);
        }
        else if (a_selectedSkill == Reward::SKILL_GOLPE) {
            inv->setHitEase(inv->getHitEase() + 1);
        }
        else { // COMBO
            inv->setComboEase(inv->getComboEase() + 1);
        }
    }
    else if(_name == Reward::CHARISMA) {
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
