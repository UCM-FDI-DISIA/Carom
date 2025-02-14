#pragma once

static class PhysicsConverter{
public:
    static const int PIXELS_PER_METER = 75;

    static int meter2pixel(float meters) {
        return meters * PIXELS_PER_METER;
    }

    static float pixel2meter(int pixel){
        return pixel/PIXELS_PER_METER;
    }
};