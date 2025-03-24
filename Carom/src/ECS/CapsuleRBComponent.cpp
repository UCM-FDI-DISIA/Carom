#include "CapsuleRBComponent.h"
#include "CaromScene.h"

using namespace ecs;


/// @brief Constructor for a capsule. The capsule is constructed horizontally.
/// @param ent the entity
/// @param pos the position
/// @param bodyType the type of body
/// @param width the distance between the two circles plus both radius
/// @param height the diameter of the circles that constitute the capsule
/// @param density the density
/// @param friction the friction
/// @param restitution the restitution
/// @param linearDamping the friction with the ground
/// @param sensor if is only a trigger collider
CapsuleRBComponent::CapsuleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, float width, float height, bool sensor, b2Rot rotation, float density, float friction, float restitution, float linearDamping, bool bullet) 
    : RigidBodyComponent(ent)
{
    _myProps.bodyType = bodyType;
    _myProps.initialPos = pos;
    _myProps.dimensions.x = width;
    _myProps.dimensions.y = height;
    _myProps.density = density;
    _myProps.friction = friction;
    _myProps.restitution = restitution;
    _myProps.isBullet = bullet;
    _myProps.isSensor = sensor;
    _myProps.linearDamping = linearDamping;
    _myProps.rotation = rotation;
    _myProps.enableContactEvents = !sensor;
    _myProps.enableSensorEvents = sensor;

    generateBodyAndShape();

    b2Capsule a_capsule;
    a_capsule.radius = height;
    a_capsule.center1 = {pos.x - (width - height)/2, pos.y};
    a_capsule.center2 = {pos.x + (width - height)/2, pos.y};

    _myB2ShapeId = b2CreateCapsuleShape(_myB2BodyId, _myB2ShapeDef, &a_capsule);
}

void
CapsuleRBComponent::updateScale(){
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
    _myB2ShapeDef = bodyShapeTuple.second;

    b2Capsule a_capsule;
    a_capsule.radius = _radius * newScale.x;

    if(_center1.x > _center2.x) {_center1.x += _center1.x * newScale.x; _center2.x -= _center2.x * newScale.x;}
    else if (_center2.x > _center1.x) {_center2.x += _center2.x * newScale.x; _center1.x -= _center1.x * newScale.x;}
    
    if(_center1.y > _center2.y) {_center1.y += _center1.y * newScale.y; _center2.y -= _center2.y * newScale.y;}
    else if (_center2.y > _center1.y) {_center2.y += _center2.y * newScale.y; _center1.y -= _center1.y * newScale.y;}

    b2CreateCapsuleShape(_myB2BodyId, bodyShapeTuple.second, &a_capsule);
    */

    _myScale = _scaleBuffer.second;

    b2Capsule a_capsule;
    a_capsule.radius = _myProps.dimensions.y * _myScale.x;

    float width = _myProps.dimensions.x * _myScale.x;
    float height = _myProps.dimensions.y * _myScale.y;

    a_capsule.center1 = {_myProps.initialPos.x - (width - height)/2, 
                         _myProps.initialPos.y};
    a_capsule.center2 = {_myProps.initialPos.x + (width - height)/2, 
                         _myProps.initialPos.y};


    b2Shape_SetCapsule(_myB2ShapeId, &a_capsule);
}