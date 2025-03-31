#include "InventoryManager.h"
#include "Texture.h"

InventoryManager::InventoryManager() 
: _inventory(Inventory())
{

}

InventoryManager::~InventoryManager() {

}

void InventoryManager::swapInventory(Inventory inv) {
    // TODO
}

std::vector<entity_t> InventoryManager::getBalls() {
    std::vector<entity_t> balls;
    balls.reserve(_inventory.MAX_BALLS);

    for(entity_t b : _inventory._balls)
        balls.push_back(b);

    return balls;
}

Texture* InventoryManager::getStickTexture() {
    return _inventory._stick.texture;
}

StickEffectComponent* InventoryManager::getStickEffect() {
    return _inventory._stick.effect;
}
