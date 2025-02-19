#pragma once
#include "Vector2D.h"
#include <vector>
#include "RandomNumberGenerator.h"
#include "RandomItem.h"

class RNG_Manager
{
    RandomNumberGenerator _rng;

    public:
    RNG_Manager() : _rng(RandomNumberGenerator()) {}
    ~RNG_Manager() {}

    void inseminate(unsigned seed) {
        _rng.Inseminate(seed);
    }
    
    template<typename T>
    RandomItem<T> getRandomItem(std::vector<RandomItem<T>>& itemsVector)
    {
        float totalProbability = 0;

        for(auto item : itemsVector) totalProbability += item.probability;

        float currentProbability = 0;
        float randomValue = _rng.nextFloat(0, totalProbability);

        for(auto item : itemsVector){
            currentProbability += item.probability;
            if (randomValue <= currentProbability) return item;
        }
        return itemsVector[itemsVector.size() - 1];
    }

    private:
};