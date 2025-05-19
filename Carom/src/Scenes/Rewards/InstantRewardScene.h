#pragma once
#include "RewardScene.h"

#include <unordered_map>

/// @brief Clase de la que heredan todas las recompensas que alteran el inventario, con funcionalidad para manejar elecciones
class InstantRewardScene : public RewardScene 
{
public:
    InstantRewardScene(Game* game, Reward reward, int maxItems);
protected:
    /// @brief Adds an element to de selected item vector and if full enables apply reward button
    /// @param item 1-6 balls in each slot, 0 is stick 
    void selectItem(int item);

    /// @brief Returns a vector of size max items that contains the indexes of selected items
    std::vector<int> getSelectedItems();

private:
    int _maxItems;
    int _selectedAmmount = 0;
    bool _selectedItems[7];
};