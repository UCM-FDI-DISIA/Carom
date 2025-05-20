#include "InstantRewardScene.h"

#include <iostream>

InstantRewardScene::InstantRewardScene(Game* game, Reward reward, int maxItems) 
: RewardScene(game, reward),
_maxItems(maxItems) {
    for (int i = 0; i < 7; ++i) {
        _selectedItems[i] = false;
    }
}

void
InstantRewardScene::selectItem(int item) {

    if (item < 7 && item > -1) {
        if (!_selectedItems[item]) {
            if (_selectedAmount < _maxItems) {
                _selectedItems[item] = true;
                ++_selectedAmount;
            }
        }
        else {
            _selectedItems[item] = false;
            --_selectedAmount;
        }
    }
    else {
        //throw cosa
        #ifdef _DEBUG
        std::cout << "Hijoputa esto no vale " << item << "\n";
        #endif
    }
}

std::vector<int>
InstantRewardScene::getSelectedItems() {
    std::vector<int> selectedIndexes;

    for(int i = 0; i < 7; ++i) 
        if(_selectedItems[i]) selectedIndexes.push_back(i);
        
    return selectedIndexes;
}

bool 
InstantRewardScene::isSelected(int index) {
    auto items = getSelectedItems();
    return std::find(items.begin(), items.end(), index) != items.end();
}

void
InstantRewardScene::toggleExitButton() {
    if(getSelectedAmount() == getMaxItems())
        showExitButton();
    else hideExitButton();
}