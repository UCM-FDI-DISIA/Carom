#include "FusionRewardScene.h"
#include "Button.h"
#include "InventoryManager.h"
#include "PoolScene.h"

FusionRewardScene::FusionRewardScene(Game* game, Reward reward)
    : InstantRewardScene(game, reward, 2)
{
    #ifdef _DEBUG
        std::cout << "FUSION" << std::endl;
    #endif
}

FusionRewardScene::~FusionRewardScene() {}

void FusionRewardScene::atRender() {
    std::vector<ButtonWithSlot> buttonsAndSlots = openInventory();
    
    for(ButtonWithSlot pair : buttonsAndSlots) 
        pair.button->setOnClick([this, pair] {this->selectItem(pair.slot);});
}

void FusionRewardScene::applyReward() {
    std::vector<int> selectedBalls = getSelectedItems();

    std::vector<PoolScene::EffectType> effectsToAdd, firstBallEffects, secondBallEffects;
    firstBallEffects = InventoryManager::Instance()->getEffectsFromBall(selectedBalls[0]);
    secondBallEffects = InventoryManager::Instance()->getEffectsFromBall(selectedBalls[1]);

    for(PoolScene::EffectType effect : firstBallEffects) {
        if(std::find(secondBallEffects.begin(), secondBallEffects.end(), effect) == secondBallEffects.end())
            secondBallEffects.push_back(effect);
    }

    InventoryManager::Instance()->removeBall(selectedBalls[0]);
    InventoryManager::Instance()->removeBall(selectedBalls[1]);

    std::vector<int> effectIdsToInt;
    for(PoolScene::EffectType effect : secondBallEffects)
        effectIdsToInt.push_back(int(effect));

    InventoryManager::Instance()->addBall(effectIdsToInt);
}

void FusionRewardScene::initObjects() {
    RewardScene::initObjects();
}

void FusionRewardScene::initFunctionalities() {
    RewardScene::initFunctionalities();
}