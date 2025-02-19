#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "B2Manager.h"

#include <exception>

using namespace ecs;

/// @brief Constructor of RigidBody. Receives a Shape class as a parameter depending on which shape is needed (circle, capsule or polygon)
/// @param ent The owner of the component
/// @param type The type of the component (kinematic, dynamic or static)
/// @param density The density of the object
/// @param friction The friction of the object
/// @param restitution The restitution of the object
/// @param shape The shape of the rigid body. Can be CircleShape, CapsuleShape or PolygonShape.
RigidBodyComponent::RigidBodyComponent(entity_t ent, b2BodyType type, Shape *shape, float density, float friction, float restitution) 
    : InfoComponent(ent)
{
    _bodyId = new b2BodyId();

    switch (shape->getType()) {
        case shape::CIRCLE: {
            CircleShape* circle = static_cast<CircleShape*>(shape);
            _bodyId = b2mngr().addRigidbody(ent, type, *circle->getCircle(), density, friction, restitution);
            break;
        }
        case shape::CAPSULE: {
            CapsuleShape* capsule = static_cast<CapsuleShape*>(shape);
            _bodyId = b2mngr().addRigidbody(ent, type, *capsule->getCapsule(), density, friction, restitution);
            break;
        }
        case shape::POLYGON: {
            PolygonShape* polygon = static_cast<PolygonShape*>(shape);
            _bodyId = b2mngr().addRigidbody(ent, type, *polygon->getPolygon(), density, friction, restitution);
            break;
        }
    }
}

RigidBodyComponent::~RigidBodyComponent(){
    B2Manager::Instance()->removeBody(_bodyId);
}

/// @brief Changes the body type.
/// @param newType New type of the RigidBody.
void
RigidBodyComponent::changeBodyType(b2BodyType newType){
    b2Body_SetType(*_bodyId, newType);
}

/// @brief Applies force at the specified offset origin point
/// @param force the vector force to apply
/// @param origin the offset. {0,0} is the center of the object
void
RigidBodyComponent::applyForceToObject(b2Vec2 force, b2Vec2 origin){
    b2Vec2 a_b2t = b2Body_GetPosition(*_bodyId);
    b2Body_ApplyForce(*_bodyId, force, origin + a_b2t, false);
}

/// @brief Applies force at the specified world origin point
/// @param force the vector force to apply
/// @param origin the world point. {0,0} is the point {0,0} of the world
void
RigidBodyComponent::applyForceToWorld(b2Vec2 force, b2Vec2 origin){
    b2Body_ApplyForce(*_bodyId, force, origin, false);
}

/// @brief Applies force at the center of the object
/// @param force the vector force to aplly
void
RigidBodyComponent::applyForceToCenter(b2Vec2 force){
    b2Body_ApplyForceToCenter(*_bodyId, force, false);
}

/// @brief Applies impulse at the specified offset origin point
/// @param impulse the vector impulse to apply
/// @param origin the offset. {0,0} is the center of the object
void
RigidBodyComponent::applyImpulseToObject(b2Vec2 impulse, b2Vec2 origin){
    b2Vec2 a_b2t = b2Body_GetPosition(*_bodyId);
    b2Body_ApplyLinearImpulse(*_bodyId, impulse, origin + a_b2t, false);
}

/// @brief Applies impulse at the specified world origin point
/// @param impulse the vector impulse to apply
/// @param origin the world point. {0,0} is the point {0,0} of the world
void
RigidBodyComponent::applyImpulseToWorld(b2Vec2 impulse, b2Vec2 origin){
    b2Body_ApplyLinearImpulse(*_bodyId, impulse, origin, false);
}

/// @brief Applies impulse at the center of the object
/// @param impulse the vector impulse to aplly
void
RigidBodyComponent::applyImpulseToCenter(b2Vec2 impulse){
    b2Body_ApplyLinearImpulseToCenter(*_bodyId, impulse, false);
}

/// @brief Changes the density of every Shape of the object
/// @param density the new density for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setDensity(float density, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(*_bodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetDensity(shapes[i], density, true);
    }
}

/// @brief Changes the friction of every Shape of the object
/// @param density the new friction for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setFriction(float friction, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(*_bodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetFriction(shapes[i], friction);
    }
}

/// @brief Changes the restitution of every Shape of the object
/// @param density the new restitution for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setRestitution(float restitution, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(*_bodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetRestitution(shapes[i], restitution);
    }
}

/*
* Generates the shape of a circle. The center of the circle will be at the center of the object
*/
CircleShape::CircleShape(float radius){
    _circle.center = {0.0, 0.0};
    _circle.radius = radius;
    _shapeType = shape::CIRCLE;
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