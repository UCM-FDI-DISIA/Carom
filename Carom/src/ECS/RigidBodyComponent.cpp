#include "RigidBodyComponent.h"
#include "TransformComponent.h"

using namespace ecs;

RigidBodyComponent::RigidBodyComponent(Entity* ent, b2BodyId body, TransformComponent* transform) : PhysicsComponent(ent), _transform(transform), _body(body) {}

