#pragma once
#include "Vector2D.h"
class b2Vec2;

class Camera{
public:
    //su posicion es publica porque me parece mas comoda para animarla asi sin usarla getters ni setters
    int x =0;
    int y =0;

    //setea la posicion de la camara con una linea
    void setPos(int newX, int newY);
    //convierte la posicion fisica en posicion en la pantalla DEPENDIENTE de la posicion de la camara
    std::pair<int,int> getRenderPos(b2Vec2 physicalPos);
};