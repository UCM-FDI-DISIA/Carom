#pragma once

#include <box2D/box2D.h>
#include "ecs.h"
#include "Vector2D.h"

#include "InfoComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"


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
        // TransformComponent(Entity* ent);
        __CMPID_DECL__(cmp::TRANSFORM);

        TransformComponent(Entity* ent) : InfoComponent(ent), _position(Vector2D(0, 0)), _scale({1,1}), _rotation(0) {}
        virtual ~TransformComponent(){}

        // Getters
        inline Vector2D getPosition(){return _position;}
        inline Scale getScale(){return _scale;}
        inline double getRotation(){return _rotation;}

        // Setters
        inline void setPosition(Vector2D newPos){_position = newPos;}
        inline void setScale(Scale newScale){_scale = newScale;}
        inline void setRotation(double newRot){_rotation = newRot;}

        // ! test
        inline void update() {
            setPosition(Vector2D(
                _myEntity->getComponent<RigidBodyComponent>()->getB2Transform().p.x,
                _myEntity->getComponent<RigidBodyComponent>()->getB2Transform().p.y
            ));
        }
    };
}