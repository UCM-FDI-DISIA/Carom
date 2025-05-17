#include "CircleRBComponent.h"
#include "CaromScene.h"

/// @brief Constructor for Circle RB
/// @param ent the entity
/// @param pos the position
/// @param bodyType the type of body
/// @param radius the radius
/// @param density the density
/// @param friction the friction
/// @param restitution the restitution
/// @param linearDamping the friction with the ground
/// @param sensor if is only a trigger collider
CircleRBComponent::CircleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, float radius, bool sensor, b2Rot rotation, float density, float friction, float restitution, float linearDamping, bool bullet) 
    : RigidBodyComponent(ent)
{
    _myProps.bodyType = bodyType;
    _myProps.initialPos = pos;
    _myProps.radius = radius;
    _myProps.density = density;
    _myProps.friction = friction;
    _myProps.restitution = restitution;
    _myProps.isBullet = bullet;
    _myProps.isSensor = sensor;
    _myProps.linearDamping = linearDamping;
    _myProps.rotation = rotation;
    _myProps.enableContactEvents = !sensor;
    _myProps.enableSensorEvents = sensor;

    _initialRadius = radius;

    calculateMass();
    generateBodyAndShape();

    b2Circle a_circle;
    a_circle.radius = _myProps.radius;
    a_circle.center = {0, 0};
    _myB2ShapeId = b2CreateCircleShape(_myB2BodyId, _myB2ShapeDef, &a_circle);
}

void
CircleRBComponent::updateScale(){
    /*_myScale = newScale;

    b2ShapeId shapes[1];
    b2Body_GetShapes(_myB2BodyId, shapes, 1);

    b2Vec2 pos = getPosition();
    b2BodyType type = b2Body_GetType(_myB2BodyId);
    float density = b2Shape_GetDensity(shapes[0]);
    float friction = b2Shape_GetFriction(shapes[0]);
    float restitution = b2Shape_GetRestitution(shapes[0]);

    b2DestroyShape(shapes[0], false);
    b2DestroyBody(_myB2BodyId);

    CaromScene* scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());

    std::pair<b2BodyId, b2ShapeDef*> bodyShapeTuple = scene->generateBodyAndShape(_myEntity, pos, type, density, friction, restitution);
    _myB2BodyId = bodyShapeTuple.first;

    b2Circle a_circle;
    a_circle.radius = _radius * newScale.x;
    a_circle.center = {0, 0};

    b2CreateCircleShape(_myB2BodyId, bodyShapeTuple.second, &a_circle);

    static_cast<CaromScene*>(&_myEntity->getScene())->disablePhysics();*/

    _myScale = _scaleBuffer.second;

    b2Circle a_circle;
    a_circle.radius = _myProps.radius * _myScale.x;
    a_circle.center = {0, 0};

    b2Shape_SetCircle(_myB2ShapeId, &a_circle);
    calculateMass();
}

// Calculate mass (circle area as if it was a square)
void CircleRBComponent::calculateMass()
{
    _myProps.mass = _myProps.density * _myProps.radius*_myProps.radius;
}

void CircleRBComponent::setSize(float newSize)
{
    Scale newScale = { 
        newSize / _initialRadius,
        newSize / _initialRadius
    };
    
    setScale(newScale);
}
