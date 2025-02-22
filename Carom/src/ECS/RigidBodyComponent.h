#pragma once
#include "PhysicsComponent.h"
#include "InfoComponent.h"
#include <box2D/box2D.h>
#include "ecs.h"
#include <functional>

#include "ITransform.h"


class B2Manager;

namespace ecs{

class Shape;
class Entity;

class RigidBodyComponent : public InfoComponent, public ITransform
{
private:
    b2BodyId _myB2BodyId;

    Scale _myScale = {1.0, 1.0};

    // Collision functions
    std::function<void(Entity*)> _collisionEnterFunc;
    std::function<void(Entity*)> _collisionExitFunc;
    std::function<void(Entity*)> _triggerEnterFunc;
    std::function<void(Entity*)> _triggerExitFunc;

    // * La unica forma de escalar es rompiendo la shape y haciendo otra, se guardan estos parámetros con ese objetivo
    Shape* _myShape;
    float _density;
    float _friction;
    float _restitution;

public:
    __CMPID_DECL__(cmp::RIGIDBODY);

    RigidBodyComponent(entity_t ent, const Vector2D& pos, b2BodyType type, Shape *shape, float density = 1, float friction = 0.2, float restitution = 0.5);
    virtual ~RigidBodyComponent();

    // Getters
    Vector2D getPosition() const override;
    Scale getScale() const override;
    double getRotation() const override;
    inline b2BodyId getB2Body() const {return _myB2BodyId;}

    // Setters
    void setPosition(const Vector2D& newPos) override;
    void setScale(const Scale& newScale) override;
    void setRotation(const double& newRot) override;

    void setBodyType(b2BodyType newType);
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

    // Collision events, only called from the scene
    void onCollisionEnter(entity_t ent);
    void onCollisionExit(entity_t ent);
    void onTriggerEnter(entity_t ent); // Used for sensors
    void onTriggerExit(entity_t ent);

    // Collision events setters
    void setOnCollisionEnter(std::function<void(entity_t)> newFunc);
    void setOnCollisionExit(std::function<void(entity_t)> newFunc);
    void setOnTriggerEnter(std::function<void(entity_t)> newFunc);
    void setOnTriggerExit(std::function<void(entity_t)> newFunc);

    };

    class Shape{
    friend RigidBodyComponent;
        
    protected:
        shape::shapeId _shapeType;

        inline shape::shapeId getType() {return _shapeType;}
        virtual void setScale(double X, double Y) = 0;
        
        Shape() {}
    public:
        virtual ~Shape() {}
        
    };

    class CircleShape : public Shape{
        b2Circle _circle;

    public:
        CircleShape(float radius);

        inline b2Circle* getCircle() {return &_circle;}
        void setScale(double X, double Y) override;
    };

    class CapsuleShape : public Shape{
        b2Capsule _capsule;

    public:
        CapsuleShape(float radius, b2Vec2 firstCenter, b2Vec2 secondCenter);

        inline b2Capsule* getCapsule() {return &_capsule;}
        void setScale(double X, double Y) override;
    };

    class PolygonShape : public Shape{
        b2Polygon _polygon;

        public:
        PolygonShape(b2Vec2 vertex[], int size, float radius);
        PolygonShape(float side);
        PolygonShape(float sizex, float sizey);

        inline b2Polygon* getPolygon() {return &_polygon;}
        void setScale(double X, double Y) override;
    };



}