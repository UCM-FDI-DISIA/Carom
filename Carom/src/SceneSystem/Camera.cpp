#include "Camera.h"
#include "PhysicsUtils.h"

std::pair<int,int> Camera::getRenderPos(b2Vec2 physicalPos){
    float resX,resY;
    resX = physicalPos.x - x;
    resY = physicalPos.y - y;

    std::pair<int,int> res = PhysicsConverter::meter2pixel({resX,resY});

    return res;
}

void Camera::setPos(float newX, float newY){
    x = newX;
    y = newY;
}

Camera::Camera(float nX, float nY){
    setPos(nX,nY);
}