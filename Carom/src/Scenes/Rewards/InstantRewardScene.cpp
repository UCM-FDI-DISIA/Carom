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
            _selectedItems[item] = true;
            if (++_selectedAmmount == _maxItems) {
                showExitButton();
            }
        }
        else {
            _selectedItems[item] = false;
            --_selectedAmmount;
            hideExitButton();
        }
    }
    else {
        //throw cosa
        #ifdef _DEBUG
        std::cout << "Hijoputa esto no vale " << item << "\n";
        #endif
    }
}