#include "ColorHitManager.h"
#include "GameScene.h"

namespace ecs{
    ColorHitManager::ColorHitManager(GameScene* mainScene) : Singleton(){
        _mainScene = mainScene;
    };

    void ColorHitManager::clearAllPositions(){
        _positionsRegistered.clear();
    }

    bool ColorHitManager::checkForHitPosition(Vector2D hitPos){
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