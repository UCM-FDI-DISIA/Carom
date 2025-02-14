#include "CircleRigidBodyComponent.h"

using namespace ecs;

CircleRigidBodyComponent::CircleRigidBodyComponent(Entity* ent, b2BodyType type, float density, float friction, float restitution, float radius):RigidBodyComponent(ent, type){

}