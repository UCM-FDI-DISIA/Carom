#pragma once
#include <utility>
#include <box2D/box2D.h>

class PhysicsConverter{
public:
    static constexpr float PIXELS_PER_METER = 430.0f;

    static int meter2pixel(float meters);

    static float pixel2meter(float pixel);

    static std::pair<int,int> meter2pixel(b2Vec2 physicalVector);

    static b2Vec2 pixel2meter(int x, int y);

    static bool circleOverlap(b2Vec2 c1, float r1, b2Vec2 c2, float r2);
};