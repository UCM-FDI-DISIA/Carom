#pragma once
#include "PhysicsComponent.h"
#include <box2D/box2D.h>

class TransformComponent;
class B2Manager;

namespace ecs{
    class RigidBodyComponent : public PhysicsComponent
    {
        b2BodyId _body; // b2 Body ID
        TransformComponent* _transform; // Our transform component
        B2Manager* _manager; // Physics Manager Singleton

        public:

        RigidBodyComponent(Entity* ent, b2BodyType type, float density, float friction, float restitution, Shape shape);
        virtual ~RigidBodyComponent(){}

        // Getters
        inline b2Transform* getB2Transform(){return &b2Body_GetTransform(_body);}
        inline b2BodyId* getB2Body(){return &_body;}

        void updatePosition();
        void changeBodyType(b2BodyType newType);


    };

    class Shape{
        friend RigidBodyComponent;
        
        protected:
        enum shapeType{
            CIRCLE,
            CAPSULE,
            POLYGON
        };
        
        shapeType _shapeType;

        inline shapeType getType() {return _shapeType;}
        
        Shape() {}
        virtual ~Shape() {}
        
    };

    class CircleShape : public Shape{
        b2Circle _circle;

    public:
        CircleShape(float radius);
        inline b2Circle* getCircle() {return &_circle;}
    };

    class CapsuleShape : public Shape{
        b2Capsule _capsule;

    public:
        CapsuleShape(float radius, b2Vec2 firstCenter, b2Vec2 secondCenter); // We use Vector2D to avoid having multiple representations of vectors
        inline b2Capsule* getCapsule() {return &_capsule;}
    };

    class PolygonShape : public Shape{
        b2Polygon _polygon;

        public:
        PolygonShape(b2Vec2 vertex[], int size, float radius);
        inline b2Polygon* getPolygon() {return &_polygon;}
    };

}