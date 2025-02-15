#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "B2Manager.h"
#include <exception>

using namespace ecs;

RigidBodyComponent::RigidBodyComponent(Entity* ent, b2BodyType type, float density, float friction, float restitution, Shape shape) : PhysicsComponent(ent) 
{
    // Initialitation of Manager, Transform and entity
    _manager = B2Manager::Instance();
    try {assert(ent->tryGetComponent<TransformComponent>(ecs::TRANSFORM, _transform));}
    catch(std::exception) { throw std::exception("Trying to attach a RigidBody to an Entity without Transform"); }
    _myEntity = ent;
}

/*
* Generates the shape of a circle. The center of the circle will be at the center of the object
*/
CircleShape::CircleShape(float radius){
    _circle.center = {0.0, 0.0};
    _circle.radius = radius;
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
    if(a_hull.count == 0) throw std::exception("Something went wrong making the hull");
    _polygon = b2MakePolygon(&a_hull, radius);
}