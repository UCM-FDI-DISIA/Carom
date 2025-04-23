#pragma once
#include <math.h>
#include <queue>
#include "CaromScene.h"

class ProgressionManager {
public:
    ProgressionManager() {}
    ~ProgressionManager() {}

    inline void reset() { ante = 0; }

    void anteUp() { ante += 1; }
    inline int getAnte() const { return ante; }

    int getScoreToBeat(int baseScore) const {
        return baseScore * pow(2, ante); //Scaling Formula, may change  
    }

private:
    int ante = 0;
    int currentBoss = 0;
};