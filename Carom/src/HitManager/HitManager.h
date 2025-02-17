#pragma once
#include <unordered_set>
#include "Singleton.h"
#include "Vector2D.h"

namespace ecs{
    class HitManager : public Singleton<HitManager>{
    protected:
        std::unordered_set<Vector2D> _positionsRegistered;
    public:
        HitManager();
        void clearAllPositions();
        bool checkForHitPosition(Vector2D hitPos);
    };
}