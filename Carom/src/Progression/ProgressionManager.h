#pragma once
#include <math.h>
#include <queue>
#include "CaromScene.h"
#include "RNG_Manager.h"
#include <vector>
#include <list>

class ProgressionManager {
public:
    ProgressionManager() : _bossesList() {}
    ~ProgressionManager() {}

    inline void reset() { ante = 0; }

    void anteUp() { ante += 1; }
    inline int getAnte() const { return ante; }

    int getScoreToBeat(int baseScore) const {
        return baseScore * pow(2, ante); //Scaling Formula, may change  
    }

    void setBossesList() {
        for (int boss : _bosses) {
            if(RNG_Manager::Instance()->randomRange(0, 1) < 0.5) _bossesList.push(boss);
            else _bossesList.emplace(_bossesList.front(), boss);
        }
    }

    int getNextBoss() {
        int boss = _bossesList.front();
        _bossesList.push(boss);
        _bossesList.pop();
        return boss;
    }

private:
    int ante = 0;
    int currentBoss = 0;
    const std::vector<int> _bosses = {0,1};

    std::queue<int> _bossesList = std::queue<int>();
};