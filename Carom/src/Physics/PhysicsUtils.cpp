#include "PhysicsUtils.h"
#include "SDLUtils.h"
#include <box2D/box2D.h>
#include <math.h>

int PhysicsConverter::meter2pixel(float meters){
    return meters * PIXELS_PER_METER;
}

float PhysicsConverter::pixel2meter(float pixel){
    return pixel/PIXELS_PER_METER;
}

std::pair<int,int> PhysicsConverter::meter2pixel(b2Vec2 physicalVector){
    int halfWidth = SDLUtils::Instance()->width()/2;
    int halfHeight = SDLUtils::Instance()->height()/2;

    return {halfWidth + meter2pixel(physicalVector.x), halfHeight - meter2pixel(physicalVector.y)};
}

b2Vec2 PhysicsConverter::pixel2meter(int x, int y){
    int posFromCenterX = x - SDLUtils::Instance()->width()/2;
    int posFromCenterY = -(y - SDLUtils::Instance()->height()/2);

    b2Vec2 res = {pixel2meter(posFromCenterX), pixel2meter(posFromCenterY)};

    return res;
}

bool PhysicsConverter::circleOverlap(b2Vec2 c1, float r1, b2Vec2 c2, float r2) {
    assert(r1 >= 0 && r2 >= 0);
    double d = sqrt(pow((c1.x - c2.x), 2) + pow((c1.y - c2.y), 2));

    return (d <= (r1 + r2));
}