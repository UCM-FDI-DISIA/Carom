#include "Camera.h"
#include "PhysicsUtils.h"
#include <box2D/box2D.h>

std::pair<int,int> Camera::getRenderPos(b2Vec2 physicalPos){
    std::pair<int,int> a_camScreenPos = PhysicsConverter::meter2pixel({x,y});
    std::pair<int,int> a_objectPos = PhysicsConverter::meter2pixel(physicalPos);

    return {a_camScreenPos.first + a_objectPos.first, a_camScreenPos.second + a_objectPos.second };
}

void Camera::setPos(float newX, float newY){
    x = newX;
    y = newY;
}

Camera::Camera(float nX, float nY){
    setPos(nX,nY);
}