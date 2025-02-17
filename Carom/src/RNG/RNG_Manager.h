#pragma once
#include "Vector2D.h"
#include <vector>
#include "RandomNumberGenerator.h"
#include "RandomItem.h"

template<typename T>
class RNG_Manager
{
    RandomNumberGenerator _rng;

    public:
    RNG_Manager() : _rng(RandomNumberGenerator()) {}
    ~RNG_Manager() {}

    void inseminate(unsigned seed) {
        // _rng(RandomNumberGenerator(seed));
    }
    
    RandomItem getRandomItem(std::vector<RandomItem>& itemsVector)
    {
        float totalProbability = 0;

        for(auto item : itemsVector) totalProbability += item.probability;

        float currentProbability = 0;
        float randomValue = _rng.nextFloat(0, totalProbability);

        for(auto item : itemsVector){
            if (randomValue <= currentProbability) return item;
        }
    }

    private:
};