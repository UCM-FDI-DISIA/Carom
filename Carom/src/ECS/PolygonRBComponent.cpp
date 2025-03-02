#include "PolygonRBComponent.h"
#include "CaromScene.h"

using namespace ecs;

/// @brief Constructor for Polygon RB
/// @param ent the entity
/// @param pos the position
/// @param type the type
/// @param vertices the vertices of the polygon in order
/// @param count the number of vertices
/// @param density the density
/// @param friction the friction
/// @param restitution the restitution
/// @param radius the radius of the vertices. If you don't want them to be rounded set it to 0
PolygonRBComponent::PolygonRBComponent(
    entity_t ent, const b2Vec2 &pos, b2BodyType type, const std::vector<b2Vec2> &vertices,
    float density, float friction , float restitution, float radius) : RigidBodyComponent(ent){
    
    CaromScene* scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());

    if (scene == nullptr) { throw "La escena no es de tipo CaromScene"; }

    std::pair<b2BodyId, b2ShapeDef*> bodyShapeTuple = scene->generateBodyAndShape(ent, pos, type, density, friction, restitution);
    _myB2BodyId = bodyShapeTuple.first;
    
    const b2Vec2* a_array = vertices.data();
    b2Hull a_hull = b2ComputeHull(a_array, vertices.size());
    b2Polygon a_polygon = b2MakePolygon(&a_hull, radius);
    _vertices = vertices;
    _radius = radius;

    b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, &a_polygon);
}

void
PolygonRBComponent::setScale(const Scale& newScale){
    _myScale = newScale;

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

    const b2Vec2* a_array = _vertices.data();
    b2Hull a_hull = b2ComputeHull(a_array, _vertices.size());
    b2Polygon a_polygon = b2MakePolygon(&a_hull, _radius);

    for(int i = 0; i < _vertices.size(); ++i){
        b2Vec2 vector = a_polygon.vertices[i] - a_polygon.centroid;
        a_polygon.vertices[i].x += vector.x * (newScale.x - 1);
        a_polygon.vertices[i].y += vector.y * (newScale.y - 1);
    }

    b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, &a_polygon);
}