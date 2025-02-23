#include "ColorHitManager.h"
#include "GameScene.h"
#include "Entity.h"

    ColorHitManager::ColorHitManager(GameScene* mainScene) : Singleton(){
        _mainScene = mainScene;
    };

    void ColorHitManager::clearAllPositions(){
        _positionsRegistered.clear();
    }

    bool ColorHitManager::checkForHitPosition(Entity* first, Entity* second){
        if(_positionsRegistered[first].find(second) != _positionsRegistered[first].end()) return false;

        //si no se ha registrado el hit en esta posicion hacer cosas que se necesiten
        //-instanciar UI de puntuaje
        //scorer.add(2);
        //reproducir un sonido
        //...

        _positionsRegistered[first].insert(second);
        _positionsRegistered[second].insert(first);
        return true;
    }
