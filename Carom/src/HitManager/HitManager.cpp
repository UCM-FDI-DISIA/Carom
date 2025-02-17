#include "HitManager.h"

namespace ecs{
    HitManager::HitManager() : Singleton(){};

    void HitManager::clearAllPositions(){
        _positionsRegistered.clear();
    }

    bool HitManager::checkForHitPosition(Vector2D hitPos){

    }
}