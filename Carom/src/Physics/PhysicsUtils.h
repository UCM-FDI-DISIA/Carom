#pragma once

#include "Vector2D.h"

static class PhysicsConverter{
public:
    static const int PIXELS_PER_METER = 75;

    static int meter2pixel(float meters);

    static float pixel2meter(int pixel);
};