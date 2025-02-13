#pragma once
#include "InfoComponent.h"
#include "Vector2D.h"
#include <box2D/box2D.h>
#include "ecs.h"

namespace ecs
{
    class TransformComponent : public InfoComponent
    {
        const b2Transform* _b2Transform = nullptr; // ! REAVALIAR
        Vector2D _position;
        float _width;
        float _height;
        struct Scale{
            double x;
            double y;
        };
        Scale _scale;
        double _rotation; //In radians

    public:
        __CMPID_DECL__(cmp::TRANSFORM);

        TransformComponent(Entity* e): InfoComponent(e), _position(Vector2D(0, 0)), _scale({1,1}), _rotation(0), _width(50.0f), _height(50.0f) {};
        virtual ~TransformComponent(){};

        void init(Entity*) {}; // TODO
        void update(Entity*) override {} // !
        void render(Entity*) override {} // !
        void handleEvent(Entity*) override {} // !

        // inline Vector2D* getPosition(){return &_position;} // TODO: por qué puntero?
        inline Vector2D& getPosition(){return _position;}
        inline Scale* getScale(){return &_scale;}
        // inline double* getRotation(){return &_rotation;} // TODO: por qué puntero?
        inline double getRotation(){return _rotation;}
        inline float getWidth(){ return _width; }
        inline float getHeight(){ return _height; }


    };
}