#pragma once

template<typename T>
struct RandomItem{
    T item;
    float probability;

    RandomItem(T item, float probability) : item(item), probability(probability) {};
};