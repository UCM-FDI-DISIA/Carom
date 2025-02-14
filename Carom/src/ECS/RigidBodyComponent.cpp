#include "RigidBodyComponent.h"
#include "TransformComponent.h"

using namespace ecs;

RigidBodyComponent::RigidBodyComponent(Entity* ent, b2WorldId world,TransformComponent* transform, bodyType type) : PhysicsComponent(ent), _transform(transform){

    //Creacion de parametros para el body
    b2BodyDef a_bodyDef = b2DefaultBodyDef();

    //Asignacion de tipo
    switch (type){

        case STATIC:
            a_bodyDef.type = b2_staticBody;
            break;
        case DYNAMIC:
            a_bodyDef.type = b2_dynamicBody;
            break;
        case KINEMATIC:
            a_bodyDef.type = b2_kinematicBody;
            break;
    }

    //Posicion
    Vector2D* position = _transform->getPosition();
    a_bodyDef.position = {position->getX(), position->getY()};
    position = nullptr;

    //Creación del body
    _body = b2CreateBody(world, &a_bodyDef);
}