#include "ColorHitManager.h"
#include "CaromScene.h"
#include "Entity.h"


ColorHitManager::ColorHitManager(CaromScene* mainScene){
    _mainScene = mainScene;
};

void ColorHitManager::clearAllHits(){
    _positionsRegistered.clear();
}

bool ColorHitManager::processHitEntities(Entity* first, Entity* second){
    std::cout << "Entrado al processHitEntities" << std::endl;
    if(_positionsRegistered[first].find(second) != _positionsRegistered[first].end()) return false;

    //si no se ha registrado el hit en esta posicion hacer cosas que se necesiten
    //Añadir puntos
    _mainScene->addScore(2);
    //reproducir un sonido
    //...

    _positionsRegistered[first].insert(second);
    _positionsRegistered[second].insert(first);
    return true;
}
