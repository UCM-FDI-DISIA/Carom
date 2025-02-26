#pragma once
#include <vector>
#include "RandomItem.h"
#include <string>
#include "Vector2D.h"
#include "JSONValue.h"
#include <iostream>

class RandomItemParser
{
public:
    RandomItemParser() {};
    ~RandomItemParser() {};

    static const std::vector<RandomItem<Vector2D>> getPositions(std::string file)
    {
        std::vector<RandomItem<Vector2D>> vec;
        JSONValue* positions = JSON::ParseFromFile(file);
    
        for(auto pos : positions->AsArray())
        {
            Vector2D position;
            position.set(pos->AsObject().at("x")->AsNumber(), pos->AsObject().at("y")->AsNumber());
            vec.push_back(RandomItem<Vector2D>(position, 1));
        }
        return vec;
    }
};