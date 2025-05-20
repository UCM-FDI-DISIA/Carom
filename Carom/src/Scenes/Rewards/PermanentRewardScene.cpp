#include "PermanentRewardScene.h"
#include "ScenesManager.h"
#include "PoolScene.h"
#include "InventoryManager.h"
#include "RNG_Manager.h"


PermanentRewardScene::PermanentRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
    , _name(_reward.getName())
    , _rng(RNG_Manager::Instance())
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
    auto inv = InventoryManager::Instance();

    if(_name == Reward::CUNNING) {
        float value = _rng->randomRange(0.01f,0.03f);
        inv->setCunning(inv->getCunning() - value);
    }
    else if(_name == Reward::SKILL_GOLPE) {
        inv->setHitEase(inv->getHitEase() + 1);
    }
    else if(_name == Reward::SKILL_COMBO) {
        inv->setComboEase(inv->getComboEase() + 1);
    }
    else if(_name == Reward::SKILL_CARAMBOLA) {
        inv->setCaromEase(inv->getCaromEase() + 1);
    }
    else if(_name == Reward::CHARISMA) {
        float value = 1;
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
    if(_name == Reward::SKILL) {
        getSkillReward();
        createRewardTitle();
    }
    createRewardText();
    showExitButton();
}

void PermanentRewardScene::getSkillReward() 
{
    std::vector<RandomItem<std::string_view>> a_skillTypes = {
        {Reward::SKILL_CARAMBOLA, 1.0},
        {Reward::SKILL_GOLPE, 1.0},
        {Reward::SKILL_COMBO, 1.0}
    };

    std::string_view a_selectedSkill = _rng->getRandomItem(a_skillTypes, false);
    _name = std::string(a_selectedSkill);
}

void PermanentRewardScene::createRewardTitle()
{
    Text rewardNameText = sdlutils().texts().at(std::string(Reward::SKILL) + "_rewardName_pool");

    if(_name == Reward::SKILL_GOLPE)
        rewardNameText = {"GOLPE", rewardNameText.font, rewardNameText.color};
    else if(_name == Reward::SKILL_COMBO)
        rewardNameText = {"COMBO", rewardNameText.font, rewardNameText.color};
    else //if(_name == Reward::SKILL_CARAMBOLA)
        rewardNameText = {"CARAMBOLA", rewardNameText.font, rewardNameText.color};

    entity_t rewardName = createText(rewardNameText.text + ":", sdlutils().width()/2, 400, 1, rewardNameText.color, renderLayer::UI, 0, rewardNameText.font);
}

void PermanentRewardScene::createRewardText()
{
    Text rewardDescText = sdlutils().texts().at(_name + "_rewardDesc_reward");

    entity_t rewardDescription = createText(rewardDescText.text, sdlutils().width()/2, 550, 1, {255, 255, 255, 255}, renderLayer::UI, 1100, rewardDescText.font);
}

