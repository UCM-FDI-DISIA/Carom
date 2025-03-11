#include "RectangleRBComponent.h"
#include "CaromScene.h"

using namespace ecs;


/// @brief Constructor for Rectangular RB
/// @param ent the entity
/// @param pos the position
/// @param bodyType the type of body
/// @param width size x
/// @param height size y
/// @param density the density
/// @param friction the friction
/// @param restitution the restitution
/// @param linearDamping the friction with the ground
/// @param sensor if is only a trigger collider
RectangleRBComponent::RectangleRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, float width, float height, bool sensor, b2Rot rotation, float density, float friction, float restitution, float linearDamping, bool bullet) 
    : RigidBodyComponent(ent)
{
    _myProps.bodyType = bodyType;
    _myProps.initialPos = pos;
    _myProps.dimensions.x = width;
    _myProps.dimensions.y = height;
    _myProps.density = density;
    _myProps.friction = friction;
    _myProps.density = density;
    _myProps.restitution = restitution;
    _myProps.isBullet = bullet;
    _myProps.isSensor = sensor;
    _myProps.linearDamping = linearDamping;
    _myProps.rotation = rotation;

    generateBodyAndShape();
    
    b2Polygon a_rect = b2MakeBox(width/2, height/2);

    b2CreatePolygonShape(_myB2BodyId, _myB2ShapeDef, &a_rect);
}

void
RectangleRBComponent::setScale(const Scale& newScale){
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

    b2Polygon a_rect = b2MakeBox((_width/2) * newScale.x, (_height/2) * newScale.y);

    b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, &a_rect);
    */

    _myScale = newScale;

    b2Polygon a_rect = b2MakeBox((_myProps.dimensions.x/2) * newScale.x, (_myProps.dimensions.y/2) * newScale.y);

    b2Shape_SetPolygon(_myB2ShapeId, &a_rect);
}