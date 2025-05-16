#include "ProgressionManager.h"


void 
ProgressionManager::reset() {
    ante = 0;

    while(!_bossesList.empty())
        _bossesList.pop();

    setBossesList();
}

void 
ProgressionManager::setBossesList() {
    for (int boss : _bosses) {
        if(RNG_Manager::Instance()->randomRange(0, 1) < 0.5 || _bossesList.empty()) _bossesList.push(boss);
        else {
            int other = _bossesList.front();
            _bossesList.pop();
            _bossesList.push(boss);
            _bossesList.push(other);
        }
    }
}

int ProgressionManager::getNextBoss() {
    int boss = _bossesList.front();
    _bossesList.push(boss);
    _bossesList.pop();
    if(ante % _bosses.size() == 0) setBossesList();
    return boss;
}

int ProgressionManager::getScoreToBeat(int baseScore) const {
    return baseScore * pow(2, ante); //Scaling Formula, may change  
}