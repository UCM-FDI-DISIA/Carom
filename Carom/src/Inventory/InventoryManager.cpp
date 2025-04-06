#include "InventoryManager.h"
#include "Texture.h"

InventoryManager::InventoryManager()
{

}

InventoryManager::~InventoryManager() {

}

void InventoryManager::swapInventory(Inventory inv) {
    removeStick();
    removeAllBalls();
    _inventory = inv;
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

Inventory::Perma& 
InventoryManager::getPerma() {
    return _inventory._perma;
}

void
InventoryManager::addWhiteBall(entity_t ball) {
    if(_inventory._whiteBall != nullptr)
        delete _inventory._whiteBall;
    _inventory._whiteBall = ball;
}

void 
InventoryManager::addBall(entity_t ball) {
    int size = _inventory._balls.size();

    assert(size < _inventory.MAX_BALLS); // Can't add ball, inventory is full
    
    _inventory._balls[size] = ball;
}

void
InventoryManager::addStick(entity_t stick) {
    if(_inventory._stick != nullptr)
        removeStick();
    _inventory._stick = stick;
}

void 
InventoryManager::swapBall(entity_t in, entity_t out) {
    int index = 0;
    while(index < _inventory._balls.size() && _inventory._balls[index] != out) ++index;
    if(index >= _inventory._balls.size()) throw("Error: la bola no se encuentra en el inventario"); //!Debería incluso lanzar excepción

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
    removeStick();
    _inventory._stick = newStick;
}

void
InventoryManager::removeWhiteBall() {
    assert(_inventory._whiteBall != nullptr);
    delete _inventory._whiteBall;
    _inventory._whiteBall = nullptr;
}

void 
InventoryManager::removeBall(entity_t ball) {
    // TODO
}

void
InventoryManager::removeBall(int index) {
    // TODO
}

void InventoryManager::removeAllBalls() {
    for(entity_t b : _inventory._balls) {
        delete b;
        b = nullptr;
    }
}

void InventoryManager::removeStick() {
    assert(_inventory._stick != nullptr);
    delete _inventory._stick;
    _inventory._stick = nullptr;
}