#include "B2Manager.h"
#include <functional>

B2Manager::B2Manager(float timeStep, float subStepCount)
: _timeStep(timeStep), 
_subStepCount(subStepCount) {

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _worldId = b2CreateWorld(&worldDef);
}

B2Manager::~B2Manager() {
    b2DestroyWorld(_worldId);
}

bool
B2Manager::init(){
    // no tengo del todo claro si esto es correcto
    // igualmente no hay mucho que pueda fallar al inicio así que esto es lo que hay
    return true;
}

void
B2Manager::stepWorld() { b2World_Step(_worldId, _timeStep, _subStepCount); }

void
B2Manager::reloadWorld(){
    b2DestroyWorld(_worldId);

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _worldId = b2CreateWorld(&worldDef);
}

std::tuple<b2BodyId&, b2ShapeDef&> 
B2Manager::generateBodyAndShape (ecs::Entity* entity, b2BodyType bodyType, 
    float density, float friction, float restitution){

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = bodyType;
    bodyDef.gravityScale = 0.0f;
    // bodyDef.position = getComponent del transform;
    // bodyDef.angle = lo mismo;
    // si el transform no es fijo en cada entitydad aquí hay que generar excepción
    b2BodyId bodyId = b2CreateBody(_worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;
    shapeDef.restitution = restitution;

    _bodyEntityMap[bodyId] = entity;

    return {bodyId, shapeDef};
}

b2BodyId 
B2Manager::addRigidbody (ecs::Entity* entity, b2BodyType bodyType, const b2Circle& circle, 
    float density, float friction, float restitution) {

    auto [bId, bDef] = generateBodyAndShape(entity, bodyType, density, friction, restitution);
    b2CreateCircleShape(bId, &bDef, &circle);

    return bId;
}

b2BodyId 
B2Manager::addRigidbody (ecs::Entity* entity, b2BodyType bodyType, const b2Polygon& polygon, 
    float density, float friction, float restitution) {

    auto [bId, bDef] = generateBodyAndShape(entity, bodyType, density, friction, restitution);
    b2CreatePolygonShape(bId, &bDef, &polygon);

    return bId;
}

b2BodyId
B2Manager::addRigidbody (ecs::Entity* entity, b2BodyType bodyType, const b2Capsule& capsule, 
    float density, float friction, float restitution) {

    auto [bId, bDef] = generateBodyAndShape(entity, bodyType, density, friction, restitution);
    b2CreateCapsuleShape(bId, &bDef, &capsule);

    return bId;
}

void
B2Manager::removeBody(const b2BodyId& id) {
    b2DestroyBody(id);
    _bodyEntityMap.erase(id);
}

ecs::Entity*
B2Manager::getEntity(const b2BodyId& id) const {
    auto a = _bodyEntityMap.at(id);
    return a;    
}