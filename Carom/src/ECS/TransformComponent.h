#pragma once
#include "InfoComponent.h"
#include "Vector2D.h"
#include <box2D/box2D.h>
#include "ecs.h"

namespace ecs
{
    class TransformComponent : public InfoComponent
    {
        const b2Transform* _b2Transform = nullptr; // ! REAVALIAR: usar b2GetTransform(bodyid)
        Vector2D _position;
        struct Size{
            float width;
            float height;
        };
        struct Scale{
            double x;
            double y;
        };
        Size _size;
        Scale _scale;
        double _rotation; //In radians

    public:
        __CMPID_DECL__(cmp::TRANSFORM);
        
        TransformComponent(Entity* ent) : InfoComponent(ent), _position(Vector2D(0, 0)), _scale({1,1}), _rotation(0) {}

        virtual ~TransformComponent(){}

        // ! He usado para tests
        // TransformComponent(Entity* ent): InfoComponent(), _position(Vector2D(0, 0)), _scale({1,1}), _rotation(0), _size({50.0f, 50.0f}) {};
        // void init(Entity*) {};
        // void update(Entity*) override {}
        // void render(Entity*) override {}
        // void handleEvent(Entity*) override {}

        inline Vector2D* getPosition(){return &_position;}
        inline Scale* getScale(){return &_scale;}
        inline double* getRotation(){return &_rotation;}

        inline float getWidth(){ return _size.width; }
        inline float getHeight(){ return _size.height; }

    };
}