#include "B2Manager.h"
#include "TransformComponent.cpp"
#include <functional>
#include <exception>

/// @brief Creación de manager y mundo de la simulación física
B2Manager::B2Manager(){

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _worldId = b2CreateWorld(&worldDef);

    _timeStep = 1.0f / 60.0f; 
    _subStepCount = 4;
}

/// @brief Destruye la simulación
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

/// @brief Destruye la simulación física y crea una nueva generando un mundo vacío
void
B2Manager::reloadWorld(){
    b2DestroyWorld(_worldId);

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _worldId = b2CreateWorld(&worldDef);

    _bodyEntityMap.clear();
}

/// @brief Función interna para generar un body y las propiedades de forma de una manera centralizada
/// @param entity Entidad a la que pertenecen estas definiciones
/// @param bodyType Tipo de cuerpo (dinámico, estático o kinemático)
/// @param density (0.0-1.0)La masa del cuerpo
/// @param friction (0.0-1.0) La cancelación de fuerza al arrastrarse con otros objetos
/// @param restitution (0.0-1.0) El rebote o elasticidad el objeto
/// @return 
std::tuple<b2BodyId&, b2ShapeDef&> 
B2Manager::generateBodyAndShape (ecs::Entity* entity, b2BodyType bodyType, 
    float density, float friction, float restitution){

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = bodyType;
    bodyDef.gravityScale = 0.0f;
    TransformComponent* transform;
    if (entity->tryGetComponent<TransformComponent>(transform))
    {
        throw std::invalid_argument("RUNTIME ERROR: Entity does not contain a TransformComponent");
    }
    else
    {
        Vector2D* pos = transform->getPosition();
        bodyDef.position.x = pos->getX();
        bodyDef.position.x = pos->getY();

        bodyDef.rotation = b2MakeRot(*transform->getRotation());
    }
    b2BodyId bodyId = b2CreateBody(_worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.friction = friction;
    shapeDef.restitution = restitution;

    _bodyEntityMap[bodyId] = entity;

    return {bodyId, shapeDef};
}

/// @brief Añade al mundo de la simulación un rigidbody circular
/// @param entity Entidad a la que pertenecen estas definiciones
/// @param bodyType Tipo de cuerpo (dinámico, estático o kinemático)
/// @param circle Definición geométrica del círculo
/// @param density (0.0-1.0)La masa del cuerpo
/// @param friction (0.0-1.0) La cancelación de fuerza al arrastrarse con otros objetos
/// @param restitution (0.0-1.0) El rebote o elasticidad el objeto
/// @return 
b2BodyId 
B2Manager::addRigidbody (ecs::Entity* entity, b2BodyType bodyType, const b2Circle& circle, 
    float density, float friction, float restitution) {

    auto [bId, bDef] = generateBodyAndShape(entity, bodyType, density, friction, restitution);
    b2CreateCircleShape(bId, &bDef, &circle);

    return bId;
}

/// @brief Añade al mundo de la simulación un rigidbody poligonal
/// @param entity Entidad a la que pertenecen estas definiciones
/// @param bodyType Tipo de cuerpo (dinámico, estático o kinemático)
/// @param polygon Definición geométrica del un polígono según sus vértices (loop)
/// @param density (0.0-1.0)La masa del cuerpo
/// @param friction (0.0-1.0) La cancelación de fuerza al arrastrarse con otros objetos
/// @param restitution (0.0-1.0) El rebote o elasticidad el objeto
/// @return 
b2BodyId 
B2Manager::addRigidbody (ecs::Entity* entity, b2BodyType bodyType, const b2Polygon& polygon, 
    float density, float friction, float restitution) {

    auto [bId, bDef] = generateBodyAndShape(entity, bodyType, density, friction, restitution);
    b2CreatePolygonShape(bId, &bDef, &polygon);

    return bId;
}

/// @brief Añade al mundo de la simulación un rigidbody cápsula
/// @param entity Entidad a la que pertenecen estas definiciones
/// @param bodyType Tipo de cuerpo (dinámico, estático o kinemático)
/// @param capsule Definición de la cápsula
/// @param density (0.0-1.0)La masa del cuerpo
/// @param friction (0.0-1.0) La cancelación de fuerza al arrastrarse con otros objetos
/// @param restitution (0.0-1.0) El rebote o elasticidad el objeto
/// @return 
b2BodyId
B2Manager::addRigidbody (ecs::Entity* entity, b2BodyType bodyType, const b2Capsule& capsule, 
    float density, float friction, float restitution) {

    auto [bId, bDef] = generateBodyAndShape(entity, bodyType, density, friction, restitution);
    b2CreateCapsuleShape(bId, &bDef, &capsule);

    return bId;
}

/// @brief Elimina un cuerpo de la simulación del mundo
/// @param id id del cuerpo en el mundo
void
B2Manager::removeBody(const b2BodyId& id) {
    b2DestroyBody(id);
    _bodyEntityMap.erase(id);
}

/// @brief Devuelve la entidad a la que pertenece el id
/// @param id id del cuerpo asociado a la entidad
/// @return 
ecs::Entity*
B2Manager::getEntity(const b2BodyId& id) const {
    auto a = _bodyEntityMap.at(id);
    return a;    
}