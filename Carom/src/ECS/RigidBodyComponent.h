#pragma once
#include "PhysicsComponent.h"
#include <box2D/box2D.h>
#include "ecs.h"


class B2Manager;

namespace ecs{

class TransformComponent;

    class RigidBodyComponent : public InfoComponent
    {
        __CMPID_DECL__(cmp::RIGIDBODY);

        b2BodyId _body; // b2 Body ID

        public:

        RigidBodyComponent(Entity* ent, b2BodyType type, Shape shape, float density = 1, float friction = 0.2, float restitution = 0.5);
        virtual ~RigidBodyComponent();

        // Getters
        inline b2Transform* getB2Transform(){return &b2Body_GetTransform(_body);}
        inline b2BodyId* getB2Body(){return &_body;}

        // Setters
        void changeBodyType(b2BodyType newType);
        void setDensity(float density, int nShapes = 1);
        void setFriction(float friction, int nShapes = 1);
        void setRestitution(float restitution, int nShapes = 1);

        // Force appliers
        void applyForceToObject(b2Vec2 force, b2Vec2 origin);
        void applyForceToWorld(b2Vec2 force, b2Vec2 origin);
        void applyForceToCenter(b2Vec2 force);

        // Impulse appliers
        void applyImpulseToObject(b2Vec2 impulse, b2Vec2 origin);
        void applyImpulseToObject(b2Vec2 impulse, b2Vec2 origin);
        void applyImpulseToCenter(b2Vec2 impulse);

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
        PolygonShape(float side);
        PolygonShape(float sizex, float sizey);
        inline b2Polygon* getPolygon() {return &_polygon;}
    };

}