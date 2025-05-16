#include "FusionRewardScene.h"
#include "Button.h"
#include "InventoryManager.h"

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


}

void FusionRewardScene::initObjects() {
    RewardScene::initObjects();
}

void FusionRewardScene::initFunctionalities() {
    RewardScene::initFunctionalities();
}