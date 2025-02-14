#pragma once

static class PhysicsConverter{
public:
    const int PIXELS_PER_METER = 75;

    int meter2pixel(float meters) {
        return meters * PIXELS_PER_METER;
    }

    float pixel2meter(int pixel){
        return pixel/PIXELS_PER_METER;
    }
};