#pragma once
#include <math.h>
#include <queue>
#include "RNG_Manager.h"
#include <vector>
#include <list>

class CaromScene; // Forward declaration

class ProgressionManager {
public:
    ProgressionManager() : _bossesList() {}
    ~ProgressionManager() {}

    //Balatro balatrez está jugando balatro         - Diego
    inline void reset() { ante = 0; }
    inline void anteUp() { ante += 1; }
    inline int getAnte() const { return ante; }

    int getScoreToBeat(int baseScore) const;

    void setBossesList();

    int getNextBoss();

private:
    int ante = 0;
    const std::vector<int> _bosses = {0,1};

    std::queue<int> _bossesList = std::queue<int>();
};