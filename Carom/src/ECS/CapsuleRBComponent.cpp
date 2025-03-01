#include "CapsuleRBComponent.h"
#include "CaromScene.h"

using namespace ecs;

CapsuleRBComponent::CapsuleRBComponent(entity_t ent, const Vector2D& pos, b2BodyType type, float radius, b2Vec2 center1, b2Vec2 center2, float density, float friction , float restitution) : RigidBodyComponent(ent){
    CaromScene* scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());

    if (scene == nullptr) { throw "La escena no es de tipo CaromScene"; }

    std::pair<b2BodyId, b2ShapeDef*> bodyShapeTuple = scene->generateBodyAndShape(ent, pos, type, density, friction, restitution);
    _myB2BodyId = bodyShapeTuple.first;

    b2Capsule a_capsule;
    a_capsule.radius = radius;
    a_capsule.center1 = center1;
    a_capsule.center2 = center2;
    _radius = radius;
    _center1 = center1;
    _center2 = center2;

    b2CreateCapsuleShape(_myB2BodyId, bodyShapeTuple.second, &a_capsule);
}

void
CapsuleRBComponent::setScale(const Scale& newScale){
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

    b2Capsule a_capsule;
    a_capsule.radius = _radius * newScale.x;

    if(_center1.x > _center2.x) {_center1.x += _center1.x * newScale.x; _center2.x -= _center2.x * newScale.x;}
    else if (_center2.x > _center1.x) {_center2.x += _center2.x * newScale.x; _center1.x -= _center1.x * newScale.x;}
    
    if(_center1.y > _center2.y) {_center1.y += _center1.y * newScale.y; _center2.y -= _center2.y * newScale.y;}
    else if (_center2.y > _center1.y) {_center2.y += _center2.y * newScale.y; _center1.y -= _center1.y * newScale.y;}

    b2CreateCapsuleShape(_myB2BodyId, bodyShapeTuple.second, &a_capsule);
}