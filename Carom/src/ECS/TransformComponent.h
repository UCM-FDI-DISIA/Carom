#pragma once
#include "InfoComponent.h"
#include "Vector2D.h"
#include <box2D/box2D.h>

namespace ecs{
    class TransformComponent : public InfoComponent{
        const b2Transform* _b2Transform = nullptr;
        Vector2D _position;
        struct Scale{
            double x;
            double y;
        };
        Scale _scale;
        double _rotation; //In radians

    public:
        TransformComponent():_position(Vector2D(0, 0)), _scale({1,1}), _rotation(0) {}
        virtual ~TransformComponent(){}

        inline Vector2D* getPosition(){return &_position;}
        inline Scale* getScale(){return &_scale;}
        inline double* getRotation(){return &_rotation;}
    };
}