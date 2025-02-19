#pragma once

#include <box2D/box2D.h>
#include "ecs.h"
#include "Vector2D.h"

#include "InfoComponent.h"


namespace ecs{
    class TransformComponent : public InfoComponent{

        Vector2D _position;
        struct Scale{
            double x;
            double y;
        };
        Scale _scale;
        double _rotation; //In radians

    public:
        __CMPID_DECL__(cmp::TRANSFORM);

        TransformComponent(Entity* ent);
        virtual ~TransformComponent(){}

        // Getters
        inline Vector2D getPosition(){return _position;}
        inline Scale getScale(){return _scale;}
        inline double getRotation(){return _rotation;}

        // Setters
        inline void setPosition(Vector2D newPos){_position = newPos;}
        inline void setScale(Scale newScale){_scale = newScale;}
        inline void setRotation(double newRot){_rotation = newRot;}
    };
}