#include "RectangleRBComponent.h"
#include "CaromScene.h"

using namespace ecs;

RectangleRBComponent::RectangleRBComponent(entity_t ent, const Vector2D& pos, b2BodyType type, float width, float height, float density, float friction , float restitution) : RigidBodyComponent(ent){
    CaromScene* scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());

    if (scene == nullptr) { throw "La escena no es de tipo CaromScene"; }

    std::pair<b2BodyId, b2ShapeDef*> bodyShapeTuple = scene->generateBodyAndShape(ent, pos, type, density, friction, restitution);
    _myB2BodyId = bodyShapeTuple.first;

    b2Polygon a_rect = b2MakeBox(width/2, height/2);
    _width = width;
    _height = height;

    b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, &a_rect);
}

void
RectangleRBComponent::setScale(const Scale& newScale){
    _myScale = newScale;

    b2ShapeId shapes[1];
    b2Body_GetShapes(_myB2BodyId, shapes, 1);

    Vector2D pos = getPosition();
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
}