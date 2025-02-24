#pragma once

#include "RigidBodyComponent.h"
#include "TransformComponent.h"

#include "Entity.h"
#include "CaromScene.h"

#include "ITransform.h"

#include "Vector2D.h"

#include <exception>
#include <typeinfo>

using namespace ecs;

namespace ecs {

/// @brief Constructor of RigidBody. Receives a Shape class as a parameter depending on which shape is needed (circle, capsule or polygon)
/// @param ent The owner of the component
/// @param type The type of the component (kinematic, dynamic or static)
/// @param density The density of the object
/// @param friction The friction of the object
/// @param restitution The restitution of the object
/// @param shape The shape of the rigid body. Can be CircleShape, CapsuleShape or PolygonShape.
RigidBodyComponent::RigidBodyComponent(entity_t ent, const Vector2D& pos, b2BodyType type, Shape *shape, float density, float friction, float restitution) 
    : InfoComponent(ent), ITransform()
{

    CaromScene* scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());

    if (scene == nullptr) { throw "La escena no es de tipo CaromScene"; }

    std::pair<b2BodyId, b2ShapeDef*> bodyShapeTuple = scene->generateBodyAndShape(ent, pos, type, density, friction, restitution);

    _myB2BodyId = bodyShapeTuple.first;

    switch (shape->getType()) {
        case shape::CIRCLE: {
            CircleShape* circle = static_cast<CircleShape*>(shape);
            b2CreateCircleShape(_myB2BodyId, bodyShapeTuple.second, circle->getCircle());
            break;
        }
        case shape::CAPSULE: {
            CapsuleShape* capsule = static_cast<CapsuleShape*>(shape);
            b2CreateCapsuleShape(_myB2BodyId, bodyShapeTuple.second, capsule->getCapsule());
            break;
        }
        case shape::POLYGON: {
            PolygonShape* polygon = static_cast<PolygonShape*>(shape);
            b2CreatePolygonShape(_myB2BodyId, bodyShapeTuple.second, polygon->getPolygon());
            break;
        }
    }

    _myShape = shape;
    _density = density;
    _friction = friction;
    _restitution = restitution;

}

RigidBodyComponent::~RigidBodyComponent(){
    b2DestroyBody(_myB2BodyId);
}

/// @brief Accesor de posición
/// @return Vector posición en el mundo físico
Vector2D
RigidBodyComponent::getPosition() const {
    b2Vec2 a_b2t = b2Body_GetPosition(_myB2BodyId);
    return {a_b2t.x , a_b2t.y};
}

/// @brief Accesor de escala
/// @return Escala en x y en Y como multiplicadores
ITransform::Scale
RigidBodyComponent::getScale() const {
    return _myScale;
    
}

/// @brief Accesor de rotación
/// @return Rotación en radianes
double
RigidBodyComponent::getRotation() const {
    b2Rot a_b2r = b2Body_GetRotation(_myB2BodyId);
    return b2Atan2(a_b2r.s, a_b2r.c);
}

/// @brief Recoloca el objeto físico
/// @param newPos Posición cartesiana
void
RigidBodyComponent::setPosition(const Vector2D& newPos) {
    b2Body_SetTransform(_myB2BodyId, {newPos.getX(), newPos.getY()}, b2Body_GetRotation(_myB2BodyId));
}

/// @brief Modifica la escala del objeto. En el caso de formas que tengan radios, el valor que modifica el radio es la Y por conveniencia
/// @param newScale Multiplicadores de escala
void
RigidBodyComponent::setScale(const Scale& newScale) {
    _myScale = newScale;

    // TODO Hacer que pueda asumir más de una shape, solo si es necesario
    b2ShapeId shape[1];
    b2Body_GetShapes(_myB2BodyId, shape, 1); // * Suponemos 1 sola shape por body

    b2DestroyShape(shape[0], false);

    _myShape->setScale(newScale.x, newScale.y);

    b2ShapeDef* a_shapeDef = new b2ShapeDef(b2DefaultShapeDef());
    a_shapeDef->density = _density;
    a_shapeDef->friction = _friction;
    a_shapeDef->restitution = _restitution;
    a_shapeDef->enableContactEvents = true;
    a_shapeDef->userData = _myEntity;

    switch (_myShape->getType()) {
        case shape::CIRCLE: {
            CircleShape* circle = static_cast<CircleShape*>(_myShape);
            b2CreateCircleShape(_myB2BodyId, a_shapeDef, circle->getCircle());
            break;
        }
        case shape::CAPSULE: {
            CapsuleShape* capsule = static_cast<CapsuleShape*>(_myShape);
            b2CreateCapsuleShape(_myB2BodyId, a_shapeDef, capsule->getCapsule());
            break;
        }
        case shape::POLYGON: {
            PolygonShape* polygon = static_cast<PolygonShape*>(_myShape);
            b2CreatePolygonShape(_myB2BodyId, a_shapeDef, polygon->getPolygon());
            break;
        }
    }
}

/// @brief Asigna la rotación del objeto físico
/// @param newRot 
void
RigidBodyComponent::setRotation(const double& newRot) {
    b2Body_SetTransform(_myB2BodyId, b2Body_GetPosition(_myB2BodyId), {std::cosf(newRot), std::sinf(newRot)});
}

/// @brief Changes the body type.
/// @param newType New type of the RigidBody.
void
RigidBodyComponent::setBodyType(b2BodyType newType){
    b2Body_SetType(_myB2BodyId, newType);
}

/// @brief Applies force at the specified offset origin point
/// @param force the vector force to apply
/// @param origin the offset. {0,0} is the center of the object
void
RigidBodyComponent::applyForceToObject(b2Vec2 force, b2Vec2 origin){
    b2Vec2 a_b2t = b2Body_GetPosition(_myB2BodyId);
    b2Body_ApplyForce(_myB2BodyId, force, origin + a_b2t, false);
}

/// @brief Applies force at the specified world origin point
/// @param force the vector force to apply
/// @param origin the world point. {0,0} is the point {0,0} of the world
void
RigidBodyComponent::applyForceToWorld(b2Vec2 force, b2Vec2 origin){
    b2Body_ApplyForce(_myB2BodyId, force, origin, false);
}

/// @brief Applies force at the center of the object
/// @param force the vector force to aplly
void
RigidBodyComponent::applyForceToCenter(b2Vec2 force){
    b2Body_ApplyForceToCenter(_myB2BodyId, force, false);
}

/// @brief Applies impulse at the specified offset origin point
/// @param impulse the vector impulse to apply
/// @param origin the offset. {0,0} is the center of the object
void
RigidBodyComponent::applyImpulseToObject(b2Vec2 impulse, b2Vec2 origin){
    b2Vec2 a_b2t = b2Body_GetPosition(_myB2BodyId);
    b2Body_ApplyLinearImpulse(_myB2BodyId, impulse, origin + a_b2t, false);
}

/// @brief Applies impulse at the specified world origin point
/// @param impulse the vector impulse to apply
/// @param origin the world point. {0,0} is the point {0,0} of the world
void
RigidBodyComponent::applyImpulseToWorld(b2Vec2 impulse, b2Vec2 origin){
    b2Body_ApplyLinearImpulse(_myB2BodyId, impulse, origin, false);
}

/// @brief Applies impulse at the center of the object
/// @param impulse the vector impulse to aplly
void
RigidBodyComponent::applyImpulseToCenter(b2Vec2 impulse){
    b2Body_ApplyLinearImpulseToCenter(_myB2BodyId, impulse, false);
}

/// @brief Changes the density of every Shape of the object
/// @param density the new density for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setDensity(float density, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(_myB2BodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetDensity(shapes[i], density, true);
    }

    _density = density;
}

/// @brief Changes the friction of every Shape of the object
/// @param density the new friction for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setFriction(float friction, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(_myB2BodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetFriction(shapes[i], friction);
    }

    _friction = friction;
}

/// @brief Changes the restitution of every Shape of the object
/// @param density the new restitution for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setRestitution(float restitution, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(_myB2BodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetRestitution(shapes[i], restitution);
    }

    _restitution = restitution;
}

/// @brief Function called everytime object enters a collision
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onCollisionEnter(entity_t ent){
    for(PhysicsComponent* PC : _collisionEnter){
        PC->onCollisionEnter(ent);
    }
}

/// @brief Function called everytime object exits a collision
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onCollisionExit(entity_t ent){
    for(PhysicsComponent* PC : _collisionExit){
        PC->onCollisionExit(ent);
    }
}

/// @brief Function called everytime object enters a sensor
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onTriggerEnter(entity_t ent){
    for(PhysicsComponent* PC : _triggerEnter){
        PC->onTriggerEnter(ent);
    }
}

/// @brief Function called everytime object exits a sensor
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onTriggerExit(entity_t ent){
    for(PhysicsComponent* PC : _triggerExit){
        PC->onTriggerExit(ent);
    }
}

void
RigidBodyComponent::suscribePhysicsComponent(PhysicsComponent* PC){
    _triggerExit.push_back(PC);
    _triggerEnter.push_back(PC);
    _collisionExit.push_back(PC);
    _collisionEnter.push_back(PC);
}

/*
* Generates the shape of a circle. The center of the circle will be at the center of the object
*/
CircleShape::CircleShape(float radius){
    _circle.center = {0.0, 0.0};
    _circle.radius = radius;
    _shapeType = shape::CIRCLE;
}

/// @brief Sets the scale of a circle to y times its scale
/// @param newScale The y value of this parameter is the multiplier
void
CircleShape::setScale(double X, double Y){

    _circle.radius *= Y;
}

/*
* Generates the shape of a capsule. The position {0,0} will be the center of the object and
* the capsule will go from firstCenter to secondCenter. The radius is the distance between
* one of the centers and one point of its semicircle.
*/
CapsuleShape::CapsuleShape(float radius, b2Vec2 firstCenter, b2Vec2 secondCenter){
    _capsule.center1 = firstCenter;
    _capsule.center2 = secondCenter;
    _capsule.radius = radius;
    _shapeType = shape::CAPSULE;
}

/// @brief Changes the scale of a capsule
/// @param newScale The y value sets how much is going to increase the radius, the centers of the capsule are calculated normally
void
CapsuleShape::setScale(double X, double Y){
    // We look where to put the new centers
    // first the x
    if(_capsule.center1.x > _capsule.center2.x){
        _capsule.center1.x += _capsule.center1.x * (X - 1);
        _capsule.center2.x -= _capsule.center2.x * (X - 1);
    }
    else if (_capsule.center2.x > _capsule.center1.x){
        _capsule.center1.x -= _capsule.center1.x * (X - 1);
        _capsule.center2.x += _capsule.center2.x * (X - 1);
    }

    // then the y
    if(_capsule.center1.y > _capsule.center2.y){
        _capsule.center1.y += _capsule.center1.y * (Y - 1);
        _capsule.center2.y -= _capsule.center2.y * (Y - 1);
    }
    else if (_capsule.center2.y > _capsule.center1.y){
        _capsule.center1.y -= _capsule.center1.y * (Y - 1);
        _capsule.center2.y += _capsule.center2.y * (Y - 1);
    }

    // finally, the radius
    _capsule.radius = Y;
}

/// @brief Generates the shape of a Polygon. If there's an error making it, will throw an exception. Common causes for errors are:
/// - The vertex are too close
/// - The vertex are on a line
/// - There are less than 3 vertex
/// - There are more vertex than B2_MAX_POLYGON_VERTICES
/// @param vertex array of vertex. Must be in order (vertex[0] will make a line to vertex[1], vertex[1] to vertex[2], etc.)
/// @param size The size of the array
/// @param radius The radius that will have the curved angles. If no curve is needed set it to 0
PolygonShape::PolygonShape(b2Vec2 vertex[], int size, float radius){
    b2Hull a_hull = b2ComputeHull(vertex, size);
    if(a_hull.count == 0) throw std::invalid_argument("Something went wrong with the vertex");
    _polygon = b2MakePolygon(&a_hull, radius);
    _shapeType = shape::POLYGON;
}

/// @brief Makes a Square
/// @param size Size of square
PolygonShape::PolygonShape(float size){
    _polygon = b2MakeSquare(size);
    _shapeType = shape::POLYGON;
}

/// @brief Makes a rectangle
/// @param sizex Horizontal size of the rectangle
/// @param sizey Vertical size of the rectangle
PolygonShape::PolygonShape(float sizex, float sizey){
    _polygon = b2MakeBox(sizex, sizey);
    _shapeType = shape::POLYGON;
}

/// @brief Scales a polygon using its centroid
/// @param newScale the variation in scale
void
PolygonShape::setScale(double X, double Y){

    for(b2Vec2 vertex : _polygon.vertices){
        b2Vec2 distanceVerCen = {vertex.x - _polygon.centroid.x, vertex.y - _polygon.centroid.y};
        vertex += {distanceVerCen.x * (float)(X - 1), distanceVerCen.y * (float)(Y - 1)};
    }
}

}