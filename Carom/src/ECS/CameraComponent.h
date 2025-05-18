#pragma once

#include <box2d/box2d.h>
#include <utility>
#include "InfoComponent.h"
#include "Vector2D.h"

//Componente que tiene la entidad de Cámara. Todas las entidades se renderizan en base a la cámara, es decir, dependiendo de la posición de la cámara las entidades se van a renderizan en una posición u otra de la pantalla.
class CameraComponent: public InfoComponent{
    friend class GameScene;
    public:
        __CMPID_DECL__(cmp::CAMERA);
        CameraComponent(Entity* e);
        //Convierte la posicion fisica en posicion en la pantalla DEPENDIENTE de la posicion de la camara
        std::pair<int,int> getRenderPos(b2Vec2 physicalPos);

        //Anade interpolacion que sacude a la camara
        //@param intensity Intensidad en unidades fisicas de la sacudida
        //@param duration Duracion
        //@param dir Direccion de la sacudida
        void shakeCamera(float intensity, float duration, Vector2D dir = Vector2D{0,1});
    };
