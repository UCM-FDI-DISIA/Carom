#include "Camera.h"
#include "PhysicsUtils.h"
#include <box2D/box2D.h>

std::pair<int,int> Camera::getRenderPos(b2Vec2 physicalPos){
    std::pair<int,int> res = PhysicsConverter::meter2pixel(physicalPos);
    res.first +=x;
    res.second +=y;
    return res;
}

void Camera::setPos(int newX, int newY){
    x = newX;
    y = newY;
}

Camera::Camera(int nX, int nY){
    setPos(nX,nY);
}