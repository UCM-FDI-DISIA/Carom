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

std::vector<entity_t> 
InventoryManager::getEffectBalls() {
    std::vector<entity_t> balls;
    balls.reserve(_inventory.MAX_BALLS);

    for(entity_t b : _inventory._balls)
        balls.push_back(b);

    return balls;
}

entity_t 
InventoryManager::getWhiteBall() {
    return _inventory._whiteBall;
}

entity_t 
InventoryManager::getStick() {
    return _inventory._stick;
}

void 
InventoryManager::swapBall(entity_t in, entity_t out) {
    int index = 0;
    while(index < _inventory._balls.size() && _inventory._balls[index] != out) ++index;
    if(index >= _inventory._balls.size()) return; //!Debería incluso lanzar excepción

    delete _inventory._balls[index];
    _inventory._balls[index] = in;
}

void 
InventoryManager::swapBall(entity_t newBall, int indexOfOldBall) {
    delete _inventory._balls[indexOfOldBall];
    _inventory._balls[indexOfOldBall] = newBall;
}


void 
InventoryManager::swapStick(entity_t newStick) {
    delete _inventory._stick;
    _inventory._stick = newStick;
}
