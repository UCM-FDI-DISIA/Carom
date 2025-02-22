#include "CaromScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>

CaromScene::CaromScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward) 
{

    // Creación del mundo físico
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _myB2WorldId = b2CreateWorld(&worldDef);

    setNewState(s);

    createWhiteBall(Vector2D(-3.5f, 0.0), b2_dynamicBody, 1, 1, 1, 1, 1); // ! tst
    getEntitiesOfGroup(ecs::grp::WHITEBALL)[0]->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({5.0f, 0.0f});
    createWhiteBall(Vector2D(1, 0), b2_dynamicBody, 2, 1, 1, 1, 10); // ! tst
    getEntitiesOfGroup(ecs::grp::WHITEBALL)[1]->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({-1.0f, 1.0f});
}

void // TODO: provisory definition, add components
CaromScene::createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius, int capa) {
    ecs::entity_t e = new ecs::Entity(*this);

    ecs::CircleShape *cs = new ecs::CircleShape(radius);
    addComponent<ecs::RigidBodyComponent>(e, pos, b2_dynamicBody, cs, density, friction, restitution);

    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e);
    addComponent<ecs::RenderTextureComponent>(e, &sdlutils().images().at("tennis_ball"), capa);

    _entsByGroup[ecs::grp::WHITEBALL].push_back(e);
    _entities.push_back(e);
}

void // TODO: provisory definition, add components
CaromScene::createEffectBall(ecs::effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    ecs::entity_t e = new ecs::Entity(*this);
    addComponent<ecs::TransformComponent>(e, pos);
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e);
    // add components
    _entsByGroup[ecs::grp::EFFECTBALLS].push_back(e);
    _entities.push_back(e);
}

void CaromScene::setNewState(State* s){
    if (_currentState != nullptr) {
        _currentState->onStateExit();
        delete _currentState;
    }
    _currentState = s;
    _currentState->onStateEnter();
}

State* CaromScene::getCurrentState(){ return _currentState;}

CaromScene::~CaromScene(){
    if(_currentState != nullptr) delete _currentState;

    // el mundo debe destruirse aquí, recordad que los ids son punteros con sombrero y gabardina
    b2DestroyWorld(_myB2WorldId);
}

void CaromScene::update(){

    auto a = Game::FIXED_TIME_STEP/1000.0;

    // Como las físicas se suelen querer ejecutar antes del update esto se hace aquí mismo
    // tal vez en el futuro esto se podria delegar a una clase padre PhysicsScene o algo así
    b2World_Step(_myB2WorldId, Game::FIXED_TIME_STEP/1000.0, _b2Substeps);

    b2ContactEvents a_contactEvents = b2World_GetContactEvents(_myB2WorldId);
    manageCollisions(a_contactEvents);

    b2SensorEvents a_sensorEvents = b2World_GetSensorEvents(_myB2WorldId);

    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    _currentState->update();
    GameScene::update();
}

std::pair<b2BodyId, b2ShapeDef*> 
CaromScene::generateBodyAndShape (
    ecs::entity_t ent, const Vector2D& vec, b2BodyType bodyType, float density, float friction, float restitution){

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = bodyType;
    bodyDef.gravityScale = 0.0f;
    bodyDef.position = {vec.getX(), vec.getY()};
    bodyDef.userData = ent;

    // TODO: rotation
    // bodyDef->rotation = entity->getComponent<ecs::TransformComponent>()->getRotation();
    // si el transform no es fijo en cada entitydad aquí hay que generar excepción

    b2BodyId bodyId = b2CreateBody(_myB2WorldId, &bodyDef);

    b2ShapeDef* shapeDef = new b2ShapeDef(b2DefaultShapeDef());
    shapeDef->density = density;
    shapeDef->friction = friction;
    shapeDef->restitution = restitution;

    return {bodyId, shapeDef};
}

void
CaromScene::manageCollisions(b2ContactEvents contactEvents){
    
    for(int i = 0; i < contactEvents.beginCount; ++i){
        b2ContactBeginTouchEvent* a_enter = contactEvents.beginEvents + i;

        ecs::entity_t ent1 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->shapeIdA));
        ecs::entity_t ent2 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->shapeIdB));

        ent1->getComponent<ecs::RigidBodyComponent>()->onCollisionEnter(ent2);
        ent2->getComponent<ecs::RigidBodyComponent>()->onCollisionEnter(ent1);
    }

    for(int i = 0; i < contactEvents.endCount; ++i){
        b2ContactEndTouchEvent* a_exit = contactEvents.endEvents + i;

        ecs::entity_t ent1 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->shapeIdA));
        ecs::entity_t ent2 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->shapeIdB));

        ent1->getComponent<ecs::RigidBodyComponent>()->onCollisionExit(ent2);
        ent2->getComponent<ecs::RigidBodyComponent>()->onCollisionExit(ent1);
    }
}

void
CaromScene::manageTriggers(b2SensorEvents sensorEvents){

    for(int i = 0; i < sensorEvents.beginCount; ++i){
        b2SensorBeginTouchEvent* a_enter = sensorEvents.beginEvents + i;

        ecs::entity_t sensor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->sensorShapeId));
        ecs::entity_t visitor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->visitorShapeId));

        sensor->getComponent<ecs::RigidBodyComponent>()->onTriggerEnter(visitor);
    }

    for(int i = 0; i < sensorEvents.endCount; ++i){
        b2SensorEndTouchEvent* a_exit = sensorEvents.endEvents + i;

        ecs::entity_t sensor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->sensorShapeId));
        ecs::entity_t visitor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->visitorShapeId));

        sensor->getComponent<ecs::RigidBodyComponent>()->onTriggerExit(visitor);
    }
}