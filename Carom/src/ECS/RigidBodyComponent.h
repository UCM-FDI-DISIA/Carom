#pragma once
#include "PhysicsComponent.h"
#include "InfoComponent.h"
#include <box2D/box2D.h>
#include "ecs.h"
#include <functional>

#include "ITransform.h"


class B2Manager;

namespace ecs{

class Entity;

class RigidBodyComponent : public InfoComponent, public ITransform
{
    friend class PhysicsComponent;
    friend class GameScene;
protected:

    b2BodyId _myB2BodyId;
    Scale _myScale = {1.0, 1.0};

    // Collision functions
    std::vector<PhysicsComponent*> _collisionEnter = {};
    std::vector<PhysicsComponent*> _collisionExit = {};
    std::vector<PhysicsComponent*> _triggerEnter = {};
    std::vector<PhysicsComponent*> _triggerExit = {};

protected:

    // Collision suscribers
    void suscribePhysicsComponent(PhysicsComponent* PC);


public:
    __CMPID_DECL__(cmp::RIGIDBODY);

    RigidBodyComponent(entity_t ent);
    virtual ~RigidBodyComponent();

    // Getters
    b2Vec2 getPosition() const override;
    Scale getScale() const override;
    double getRotation() const override;
    inline b2BodyId getB2Body() const {return _myB2BodyId;}

    // Setters
    void setPosition(const b2Vec2& newPos) override;
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

    //onCollision and onTrigger Methods
    void onCollisionEnter(entity_t ent);
    void onCollisionExit(entity_t ent);
    void onTriggerEnter(entity_t ent);
    void onTriggerExit(entity_t ent);

    };
}