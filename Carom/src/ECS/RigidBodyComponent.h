#pragma once
#include "PhysicsComponent.h"
#include "InfoComponent.h"
#include "ecs.h"
#include <box2D/box2D.h>
#include <functional>
#include <cmath>
#include <math.h>

#include "ITransform.h"


class B2Manager;

namespace ecs{

class Entity;

static const b2Rot defaultRotation = {1.0f, 0.0f};

class RigidBodyComponent : public InfoComponent, public ITransform
{
    friend class PhysicsComponent;
    friend class GameScene;
protected:

    b2BodyId _myB2BodyId;
    b2ShapeDef* _myB2ShapeDef;
    b2ShapeId _myB2ShapeId;
    
    Scale _myScale = {1.0, 1.0};

    /// @brief Si es true implica que la escala debe ser cambiada a la del segundo componente
    std::pair<bool, Scale> _scaleBuffer = {false, Scale()};

    // Data used for polygons
    struct Polygon{
        std::vector<b2Vec2> vertices;
        float radius;
    };

    struct Props {
        b2BodyType bodyType;
        b2Vec2 initialPos;
        b2Rot rotation;
        float density;
        float friction;
        float restitution;
        float linearDamping;
        float sleepThreshold = 0.01;
        bool isBullet;
        bool isSensor;
        bool enableContactEvents;
        bool enableSensorEvents;

        union {
            float radius;
            float length;
            b2Vec2 dimensions;
            Polygon *polyData = nullptr;
        };
    };

    Props _myProps;

    // Collision functions
    std::vector<PhysicsComponent*> _collisionEnter = {};
    std::vector<PhysicsComponent*> _collisionExit = {};
    std::vector<PhysicsComponent*> _triggerEnter = {};
    std::vector<PhysicsComponent*> _triggerExit = {};

    // Collision suscribers
    void suscribePhysicsComponent(PhysicsComponent* PC);

    virtual void updateScale() = 0;

public:
    __CMPID_DECL__(cmp::RIGIDBODY);

    RigidBodyComponent(entity_t ent);
    virtual ~RigidBodyComponent();

    void update() override;

    void generateBodyAndShape();

    // Getters
    b2Vec2 getPosition() const override;
    Scale getScale() const override;
    double getRotation() const override;
    inline b2BodyId getB2Body() const {return _myB2BodyId;}
    inline b2Vec2 getVelocity() {return b2Body_GetLinearVelocity(_myB2BodyId);}
    inline float getLinearDamping() {return _myProps.linearDamping; }
    bool isMoving();

    // Setters
    void setPosition(const b2Vec2& newPos) override;
    void setRotation(const double& newRot) override;
    void setScale(const Scale& newScale) override;

    void setBodyType(b2BodyType newType);
    void setDensity(float density, int nShapes);
    void setDensity(float density);
    void setFriction(float friction, int nShapes);
    void setFriction(float friction);
    void setRestitution(float restitution, int nShapes);
    void setRestitution(float restitution);
    void setLinearDamping(float damping);

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