#pragma once

#include <box2D/box2D.h>
#include <utility>
#include "InfoComponent.h"
#include "Vector2D.h"


class CameraComponent: public InfoComponent{
    friend class GameScene;
    public:
        __CMPID_DECL__(cmp::CAMERA);
        CameraComponent(Entity* e);
        //convierte la posicion fisica en posicion en la pantalla DEPENDIENTE de la posicion de la camara
        std::pair<int,int> getRenderPos(b2Vec2 physicalPos);

        void shakeCamera(float intensity, float duration, Vector2D dir = Vector2D{0,1});
    };
