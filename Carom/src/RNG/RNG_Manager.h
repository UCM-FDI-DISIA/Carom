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
    T getRandomItem(std::vector<RandomItem<T>>& itemsVector, bool deleteFromVector = false)
    {
        float totalProbability = 0;

        for(auto item : itemsVector) totalProbability += item.probability;

        float currentProbability = 0;
        float randomValue = _rng.nextFloat(0, totalProbability);

        for(auto it = itemsVector.begin(); it < itemsVector.end(); it++){
            currentProbability += it->probability;
            if (randomValue <= currentProbability)
            {
                T returned = it->item;
                if(deleteFromVector) itemsVector.erase(it);
                return returned;
            }
        }
        return itemsVector[0].item;
    }

    template<typename T>
    std::vector<T> getRandomItems(std::vector<RandomItem<T>> const itemsVector, int quantity, bool replacement = true)
    {
        std::vector<T> result;

        if(quantity > itemsVector.size())
        {
            for(auto c : itemsVector) result.push_back(c.item);
            return result;
        }

        std::vector<RandomItem<T>> a_vector = itemsVector;

        for(auto c = 0; c < quantity; c++) result.push_back(getRandomItem(a_vector, !replacement));

        return result;
    }

    inline int randomRange(int x, int y) {return _rng.nextInt(x,y);};
    inline float randomRange(float x, float y){return _rng.nextFloat(x,y);};

    inline bool result(float probability){
        float r = _rng.nextFloat();
        return r < probability;
    };

    private:
};