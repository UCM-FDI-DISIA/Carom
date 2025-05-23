#include "BoxRBComponent.h"
#include "CaromScene.h"

/// @brief Constructor for Polygon RB
/// @param ent the entity
/// @param pos the position
/// @param bodyType the type of body
/// @param lenght side dimension
/// @param density the density
/// @param friction the friction
/// @param restitution the restitution
/// @param linearDamping the friction with the ground
/// @param sensor if is only a trigger collider
BoxRBComponent::BoxRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, float length, bool sensor, b2Rot rotation, float density, float friction, float restitution, float linearDamping, bool bullet) 
    : RigidBodyComponent(ent)
{
    _myProps.bodyType = bodyType;
    _myProps.initialPos = pos;
    _myProps.length = length;
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

    b2Polygon a_box = b2MakeSquare(length/2);
    _myB2ShapeId = b2CreatePolygonShape(_myB2BodyId, _myB2ShapeDef, &a_box);
}

void
BoxRBComponent::updateScale(){
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

    b2Polygon a_box = b2MakeSquare((_length/2)*newScale.x);

    b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, &a_box);
    */

    _myScale = _scaleBuffer.second;

    b2Polygon a_box = b2MakeSquare((_myProps.length/2)*_myScale.x);

    b2Shape_SetPolygon(_myB2ShapeId, &a_box);
}