#pragma once
#include <utility>
#include "Vector2D.h"

class b2Vec2;
class PhysicsConverter{
public:
    static const int PIXELS_PER_METER = 75;

    static int meter2pixel(float meters);

    static float pixel2meter(int pixel);

    static std::pair<int,int> meter2pixel(b2Vec2 physicalVector);

    static b2Vec2 pixel2meter(int x, int y);
};