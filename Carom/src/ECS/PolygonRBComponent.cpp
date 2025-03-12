#include "PolygonRBComponent.h"
#include "CaromScene.h"

using namespace ecs;


/// @brief Constructor for Polygon RB
/// @param ent the entity
/// @param pos the position
/// @param bodyType the type of body
/// @param vertices the vertices of the polygon in order
/// @param radius the radius of the vertices. If you don't want them to be rounded set it to 0
/// @param density the density
/// @param friction the friction
/// @param restitution the restitution
/// @param linearDamping the friction with the ground
/// @param sensor if is only a trigger collider
PolygonRBComponent::PolygonRBComponent(entity_t ent, const b2Vec2 &pos, b2BodyType bodyType, const std::vector<b2Vec2> &vertices, float radius, bool sensor, b2Rot rotation, float density, float friction, float restitution, float linearDamping, bool bullet) 
    : RigidBodyComponent(ent)
{
    _myProps.bodyType = bodyType;
    _myProps.initialPos = pos;
    _myProps.polyData->radius = radius;
    _myProps.polyData->vertices = vertices;
    _myProps.density = density;
    _myProps.friction = friction;
    _myProps.density = density;
    _myProps.restitution = restitution;
    _myProps.isBullet = bullet;
    _myProps.isSensor = sensor;
    _myProps.linearDamping = linearDamping;
    _myProps.rotation = rotation;
    _myProps.enableContactEvents = !sensor;
    _myProps.enableSensorEvents = sensor;

    generateBodyAndShape();
    
    const b2Vec2* a_array = _myProps.polyData->vertices.data();
    b2Hull a_hull = b2ComputeHull(a_array, _myProps.polyData->vertices.size());
    b2Polygon a_polygon = b2MakePolygon(&a_hull, _myProps.polyData->radius);

    b2CreatePolygonShape(_myB2BodyId, _myB2ShapeDef, &a_polygon);
}

void
PolygonRBComponent::setScale(const Scale& newScale){
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

    const b2Vec2* a_array = _vertices.data();
    b2Hull a_hull = b2ComputeHull(a_array, _vertices.size());
    b2Polygon a_polygon = b2MakePolygon(&a_hull, _radius);

    for(int i = 0; i < _vertices.size(); ++i){
        b2Vec2 vector = a_polygon.vertices[i] - a_polygon.centroid;
        a_polygon.vertices[i].x += vector.x * (newScale.x - 1);
        a_polygon.vertices[i].y += vector.y * (newScale.y - 1);
    }

    b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, &a_polygon);
    */

    _myScale = newScale;

    const b2Vec2* a_array = _myProps.polyData->vertices.data();
    b2Hull a_hull = b2ComputeHull(a_array, _myProps.polyData->vertices.size());
    b2Polygon a_polygon = b2MakePolygon(&a_hull, _myProps.polyData->radius);
    
    for(int i = 0; i < _myProps.polyData->vertices.size(); ++i){
        b2Vec2 vector = a_polygon.vertices[i] - a_polygon.centroid;
        a_polygon.vertices[i].x += vector.x * (newScale.x - 1);
        a_polygon.vertices[i].y += vector.y * (newScale.y - 1);
    }

    b2Shape_SetPolygon(_myB2ShapeId, &a_polygon);
}