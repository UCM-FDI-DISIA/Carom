#include "HitManager.h"
#include "GameScene.h"

namespace ecs{
    HitManager::HitManager(GameScene* mainScene) : Singleton(){
        _mainScene = mainScene;
    };

    void HitManager::clearAllPositions(){
        _positionsRegistered.clear();
    }

    bool HitManager::checkForHitPosition(Vector2D hitPos){
        if(_positionsRegistered.find(hitPos)!=_positionsRegistered.end()) return false;

        //si no se ha registrado el hit en esta posicion hacer cosas que se necesiten
        //-instanciar UI de puntuaje
        //añadir la puntuación al puntuaje final
        //reproducir un sonido
        //...

        _positionsRegistered.insert(hitPos);
        return true;
    }
}