#include "FusionRewardScene.h"
#include "Button.h"
#include "InventoryManager.h"
#include "PoolScene.h"
#include "RenderTextureComponent.h"

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
    
    if(buttonsAndSlots.size() == 1) { 
        showExitButton();
        return;
    }

    for(ButtonWithSlot pair : buttonsAndSlots) {
        if(pair.slot == 0) continue;
        getComponent<RenderTextureComponent>((pair.button)->getEntity())->changeColorTint(64, 64, 64);
        pair.button->setOnClick([this, pair] {
            this->selectItem(pair.slot);
            if(!isSelected(pair.slot)) getComponent<RenderTextureComponent>((pair.button)->getEntity())->changeColorTint(64, 64, 64);
            else getComponent<RenderTextureComponent>((pair.button)->getEntity())->resetColorTint();
        });
    }
}

void FusionRewardScene::applyReward() {
    
    std::vector<int> selectedBalls = getSelectedItems();
    if(selectedBalls.size() == 0) return;

    std::vector<RewardScene::ballID> effectsToAdd, firstBallEffects, secondBallEffects;
    firstBallEffects = InventoryManager::Instance()->getEffectsFromBall(selectedBalls[0]-1);
    secondBallEffects = InventoryManager::Instance()->getEffectsFromBall(selectedBalls[1]-1);

    for(RewardScene::ballID effect : firstBallEffects) {
        if(std::find(secondBallEffects.begin(), secondBallEffects.end(), effect) == secondBallEffects.end())
            secondBallEffects.push_back(effect);
    }

    InventoryManager::Instance()->removeBall(selectedBalls[0]-1);
    InventoryManager::Instance()->removeBall(selectedBalls[1]-1);

    std::vector<int> effectIdsToInt;
    for(RewardScene::ballID effect : secondBallEffects)
        effectIdsToInt.push_back(int(effect));

    InventoryManager::Instance()->addBall(effectIdsToInt);
}

void FusionRewardScene::initObjects() {
    RewardScene::initObjects();
}

void FusionRewardScene::initFunctionalities() {
    RewardScene::initFunctionalities();
}

bool 
FusionRewardScene::isSelected(int index) {
    auto items = getSelectedItems();

    return std::find(items.begin(), items.end(), index) != items.end();
}
