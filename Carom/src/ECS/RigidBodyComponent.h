#pragma once
#include "PhysicsComponent.h"
#include "InfoComponent.h"
#include <box2D/box2D.h>
#include "ecs.h"


class B2Manager;

namespace ecs{

class Shape;
class Entity;

class RigidBodyComponent : public InfoComponent
{
    b2BodyId *_bodyId;

    public:
    __CMPID_DECL__(cmp::RIGIDBODY);

    RigidBodyComponent(Entity* ent, b2BodyType type, Shape *shape, float density = 1, float friction = 0.2, float restitution = 0.5);
    virtual ~RigidBodyComponent();

    // Getters
    inline b2Transform getB2Transform(){return b2Body_GetTransform(*_bodyId);}
    inline b2BodyId* getB2Body(){return _bodyId;}
    inline b2Vec2 getVelocity() {return b2Body_GetLinearVelocity(*_bodyId);}
    bool isMoving();

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
    void applyImpulseToWorld(b2Vec2 impulse, b2Vec2 origin);
    void applyImpulseToCenter(b2Vec2 impulse);

    };

    class Shape{
    friend RigidBodyComponent;
        
    protected:
        shape::shapeId _shapeType;

        inline shape::shapeId getType() {return _shapeType;}
        
        Shape() {}
    public:
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