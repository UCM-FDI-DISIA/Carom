#pragma once
#include "PhysicsComponent.h"
#include "InfoComponent.h"
#include "ecs.h"
#include <functional>
#include <cmath>
#include <math.h>

#include "ITransform.h"


class Entity;

static const b2Rot defaultRotation = {1.0f, 0.0f};


// Base de los componentes de rigidbody. Utiliza el motor de físicas de box2d.
class RigidBodyComponent : public InfoComponent, public ITransform
{
    friend class PhysicsComponent;
    friend class GameScene;
protected:

    b2BodyId _myB2BodyId;
    b2ShapeDef* _myB2ShapeDef;
    b2ShapeId _myB2ShapeId;
    
    Scale _myScale = {1.0, 1.0};

    // Data used for polygons
    struct Polygon{
        std::vector<b2Vec2> vertices;
        float radius;

        Polygon(const std::vector<b2Vec2>& v, float r) : vertices(v), radius(r) {}
    };

    struct Props {
        b2BodyType bodyType;
        b2Vec2 initialPos;
        b2Rot rotation;
        float density;
        float friction;
        float restitution;
        float linearDamping;
        float sleepThreshold;
        bool isBullet;
        bool isSensor;
        bool enableContactEvents;
        bool enableSensorEvents;
        float mass;

        union {
            float radius;
            float length;
            b2Vec2 dimensions;
            Polygon *polyData = nullptr;
        };
    };
    
    Props _myProps;
    
    /// @brief Si es true implica que la escala debe ser cambiada a la del segundo componente
    std::pair<bool, Scale> _scaleBuffer = {false, Scale()};
    
    // Collision functions
    std::vector<PhysicsComponent*> _collisionEnter = {};
    std::vector<PhysicsComponent*> _collisionExit = {};
    std::vector<PhysicsComponent*> _triggerEnter = {};
    std::vector<PhysicsComponent*> _triggerExit = {};
    
    // Collision suscribers
    void suscribePhysicsComponent(PhysicsComponent* PC);
    

    void generateBodyAndShape();
    virtual void calculateMass() {}
    virtual void updateScale() = 0;

    const float TERMINAL_VELOCITY = 0.02f;

public:
    __CMPID_DECL__(cmp::RIGIDBODY);

    RigidBodyComponent(entity_t ent);
    virtual ~RigidBodyComponent();

    void update() override;

    // Getters
    b2Vec2 getPosition() const override;
    Scale getScale() const override;
    double getRotation() const override;
    inline b2BodyId getB2Body() const {return _myB2BodyId;}
    inline float getFriction() const {return b2Shape_GetFriction(_myB2ShapeId);}
    inline float getRestitution() const {return b2Shape_GetRestitution(_myB2ShapeId);}
    inline b2Vec2 getVelocity() {return b2Body_GetLinearVelocity(_myB2BodyId);}
    inline float getLinearDamping() {return _myProps.linearDamping; }
    // for circles
    inline float getRadius() {return _myProps.radius; }
    inline float getDensity() {return _myProps.density; }
    inline float getMass() {return _myProps.mass; }
    inline b2BodyType getBodyType() {return _myProps.bodyType; }
    bool isMoving();
    float getVelocityMag();

    // Setters
    void setPosition(const b2Vec2& newPos) override;
    void setRotation(const double& newRot) override;
    void setScale(const Scale& newScale) override;
    // pensado para bolas
    virtual void setSize(float newSize) {}
    void setBodyType(b2BodyType newType);
    void setDensity(float density, int nShapes);
    void setDensity(float density);
    void setFriction(float friction, int nShapes);
    void setFriction(float friction);
    void setRestitution(float restitution, int nShapes);
    void setRestitution(float restitution);
    void setLinearDamping(float damping);

    void setEnabled(bool state) override;

    // enable or disable body to participate in simulation
    void setBodyEnabled(bool enabled);

    // Force appliers
    void applyForceToObject(b2Vec2 force, b2Vec2 origin);
    void applyForceToWorld(b2Vec2 force, b2Vec2 origin);
    void applyForceToCenter(b2Vec2 force);

    // Impulse appliers
    void applyImpulseToObject(b2Vec2 impulse, b2Vec2 origin);
    void applyImpulseToWorld(b2Vec2 impulse, b2Vec2 origin);
    void applyImpulseToCenter(b2Vec2 impulse);

    //onCollision and onTrigger Methods
    void onCollisionEnter(entity_t ent, b2Manifold& contactData);
    void onCollisionExit(entity_t ent);
    void onTriggerEnter(entity_t ent);
    void onTriggerExit(entity_t ent);
    };