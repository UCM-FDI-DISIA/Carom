#include "PhysicsUtils.h"
#include "SDLUtils.h"
#include <box2D/box2D.h>

int PhysicsConverter::meter2pixel(float meters){
    return meters * PIXELS_PER_METER;
}

float PhysicsConverter::pixel2meter(int pixel){
    return pixel/PIXELS_PER_METER;
}

