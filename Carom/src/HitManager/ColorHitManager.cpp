#include "ColorHitManager.h"
#include "CaromScene.h"
#include "Entity.h"
#include "AudioManager.h"
#include "InventoryManager.h"


ColorHitManager::ColorHitManager(CaromScene* mainScene){
    _mainScene = mainScene;
    _inventory = InventoryManager::Instance();
};

void ColorHitManager::clearAllHits(){
    _positionsRegistered.clear();
}

bool ColorHitManager::processHitEntities(Entity* first, Entity* second){
    #ifdef _DEBUG
    std::cout << "Entrado al processHitEntities" << std::endl;
    #endif
    AudioManager::Instance()->playSoundEfect("hit");
    if(_positionsRegistered[first].find(second) != _positionsRegistered[first].end()) return false;

    //si no se ha registrado el hit en esta posicion hacer cosas que se necesiten
    //Añadir puntos
    _mainScene->addScore(baseComboScore + _inventory->getComboEase());
    //reproducir un sonido
    //...

    _positionsRegistered[first].insert(second);
    _positionsRegistered[second].insert(first);
    return true;
}