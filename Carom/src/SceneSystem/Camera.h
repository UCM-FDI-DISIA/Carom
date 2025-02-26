#pragma once

#include <box2D/box2D.h>
#include <utility>

class Camera{
public:
    //Posicion fisica. su posicion es publica porque me parece mas comoda para animarla asi sin usarla getters ni setters
    float x = 0;
    float y = 0;

    Camera(float nX, float nY);
    //setea la posicion de la camara con una linea
    void setPos(float newX, float newY);
    //convierte la posicion fisica en posicion en la pantalla DEPENDIENTE de la posicion de la camara
    std::pair<int,int> getRenderPos(b2Vec2 physicalPos);
};