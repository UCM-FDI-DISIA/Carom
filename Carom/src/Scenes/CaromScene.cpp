#include "CaromScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
#include "ScoreContainer.h"
#include "WhiteBallScorerComponent.h"
#include "ColorBallScorerComponent.h"
#include "RNG_Manager.h"
#include "RandomItem.h"

#include "PhysicsUtils.h"
#include "Game.h"
#include "Vector2D.h"
#include "vector"
#include <box2d/box2d.h>

namespace ecs {

    CaromScene::CaromScene(State* s, Game* g, GameScene* reward, unsigned seed) : GameScene(g), _reward(reward), _updatePhysics(true) 
    {
        // SEEDING
        _rngManager = new RNG_Manager();
        _rngManager->inseminate(seed);


        // Creación del mundo físico
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {0.0f, 0.0f};
        _myB2WorldId = b2CreateWorld(&worldDef);
        b2World_SetRestitutionThreshold(_myB2WorldId, 0.01); // para la bola rebotear más realisticamente

        setNewState(s);

        // BALL TEST
        // Converts (x, y) from screen(svg) to meters and to meter coordinates
        b2Vec2 wb_pos = PhysicsConverter::pixel2meter(
            *&sdlutils().svgElements_table().at("bola_blanca").x,
            *&sdlutils().svgElements_table().at("bola_blanca").y
        );
        createWhiteBall(wb_pos, b2_dynamicBody, 1, 0.2, 1, 10);
        // Apply impulse
        getEntitiesOfGroup(ecs::grp::WHITEBALL)[0]->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({0.0f, 0.0f});

        /*
        // Second ball
        b2Vec2 wb_pos_2 = PhysicsConverter::pixel2meter(
            *&sdlutils().svgElements_table().at("bola_blanca").x + 290,
            *&sdlutils().svgElements_table().at("bola_blanca").y
        );
        createWhiteBall(wb_pos_2, b2_dynamicBody, 1, 0.2, 1, 10);
        getEntitiesOfGroup(ecs::grp::WHITEBALL)[1]->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({-0.008, 0.0f});
        !BALL TEST
        */

        // EFFECT BALLS
        int n_eb = 3;
        int npos = sdlutils().svgElements_ballPos().size();
        assert(n_eb <= npos);
        
        std::vector<RandomItem<int>> positions;
        for(int i = 1; i <= npos; ++i)
            positions.push_back(RandomItem(i, 1.0f));

        std::vector<int> eb_selected_pos = _rngManager->getRandomItems(positions, n_eb, false);

        for(int i = 0; i < n_eb; ++i) {
            std::string s = "bola";
            if(eb_selected_pos[i] > 1)
                s += ("_" + std::to_string(eb_selected_pos[i]));
            
            auto& eb = sdlutils().svgElements_ballPos().at(s);
            auto eb_pos = PhysicsConverter::pixel2meter(eb.x, eb.y);

            createEffectBall(ecs::effect::NULO, eb_pos, b2_dynamicBody, 1, 0.2, 1, 10);
        }


        // Create table with texture and colliders
        createTable();

        _hitManager = new ColorHitManager(this);
        _scoreContainer = new ScoreContainer(200,0);
    }

    entity_t
    CaromScene::createWhiteBall(const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution, int layer) 
    {
        // SCALE
        float svgSize = *&sdlutils().svgElements_table().at("bola_blanca").width;
        float textureSize = sdlutils().images().at("bola_blanca").width();
        float scale = svgSize/textureSize;

        ecs::entity_t e = new ecs::Entity(*this);

        // RB
        float radius = PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("bola_blanca").width/2);
        ecs::CircleShape *cs = new ecs::CircleShape(radius);
        addComponent<ecs::RigidBodyComponent>(e, pos, type, cs, density, friction, restitution);

        // RENDER
        _entsRenderable.push_back(e); // Must be pushed back into renderable vector before adding the component for proper sort!
        addComponent<ecs::RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), layer, scale); // scale atera a posicao

        // SCORE
        //addComponent<ecs::WhiteBallScorerComponent>(e);

        _entsByGroup[ecs::grp::WHITEBALL].push_back(e);
        _entities.push_back(e);

        return e;
    }

    void
    CaromScene::createEffectBall(ecs::effect::effectId effectId, const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution, int layer) {
        // Scale
        float svgSize = *&sdlutils().svgElements_ballPos().at("bola").width;
        float textureSize = sdlutils().images().at("bola_blanca").width(); // TODO: cambiar a textura effect ball
        float scale = svgSize/textureSize;        
        
        ecs::entity_t e = new ecs::Entity(*this);
        
        // RB
        float radius = PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("bola_blanca").width/2);
        ecs::CircleShape *cs = new ecs::CircleShape(radius);
        addComponent<ecs::RigidBodyComponent>(e, pos, type, cs, density, friction, restitution);

        // RENDER
        _entsRenderable.push_back(e); // Must be pushed back into renderable vector before adding the component for proper sort!
        addComponent<ecs::RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), layer, scale); // TODO: cambiar a textura effect ball

        // SCORE
        addComponent<ecs::ColorBallScorerComponent>(e);

        // TODO: add components according to its id

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

        delete _hitManager;
        delete _scoreContainer;
    }

    void CaromScene::update(){

        auto a = Game::FIXED_TIME_STEP/1000.0;

        // Como las físicas se suelen querer ejecutar antes del update esto se hace aquí mismo
        // tal vez en el futuro esto se podria delegar a una clase padre PhysicsScene o algo así
        // Hay 3 porque si no había tunneling y aumentar substeps no resolvía el problema
        b2World_Step(_myB2WorldId, Game::FIXED_TIME_STEP/3000.0, _b2Substeps);
        b2World_Step(_myB2WorldId, Game::FIXED_TIME_STEP/3000.0, _b2Substeps);
        b2World_Step(_myB2WorldId, Game::FIXED_TIME_STEP/3000.0, _b2Substeps);


        b2ContactEvents a_contactEvents = b2World_GetContactEvents(_myB2WorldId);
        manageEnterCollisions(a_contactEvents);
        manageExitCollisions(a_contactEvents);

        b2SensorEvents a_sensorEvents = b2World_GetSensorEvents(_myB2WorldId);
        manageEnterTriggers(a_sensorEvents);
        manageExitTriggers(a_sensorEvents);

        enablePhysics();

        State* a_stateToChange = nullptr;
        if(_currentState->checkCondition(a_stateToChange)){
            setNewState(a_stateToChange);
        }

        _hitManager->clearAllHits();

        GameScene::update();
    }

    std::pair<b2BodyId, b2ShapeDef*> 
    CaromScene::generateBodyAndShape (
        ecs::entity_t ent, const b2Vec2& vec, b2BodyType bodyType, float density, float friction, float restitution){

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = bodyType;
        bodyDef.gravityScale = 0.0f;
        bodyDef.position = {vec.x, vec.y};
        bodyDef.userData = ent;
        bodyDef.sleepThreshold = 0.01; // velocidad mínima para dormir (aunque no funcione muy bien)
        bodyDef.isBullet = true; // para collisiones rápidas
        bodyDef.linearDamping = 0.4f; // friccíon con el suelo

        // TODO: rotation
        // bodyDef->rotation = entity->getComponent<ecs::TransformComponent>()->getRotation();
        // si el transform no es fijo en cada entitydad aquí hay que generar excepción

        b2BodyId bodyId = b2CreateBody(_myB2WorldId, &bodyDef);

        b2ShapeDef* shapeDef = new b2ShapeDef(b2DefaultShapeDef());
        shapeDef->density = density;
        shapeDef->friction = friction;
        shapeDef->restitution = restitution;
        shapeDef->enableContactEvents = true;
        shapeDef->userData = ent;


        return {bodyId, shapeDef};
    }

    void
    CaromScene::manageEnterCollisions(b2ContactEvents contactEvents){
        
        for(int i = 0; i < contactEvents.beginCount; ++i){
            b2ContactBeginTouchEvent* a_enter = contactEvents.beginEvents + i;

            ecs::entity_t ent1 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->shapeIdA));
            ecs::entity_t ent2 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->shapeIdB));

            ent1->getComponent<ecs::RigidBodyComponent>()->onCollisionEnter(ent2);
            ent2->getComponent<ecs::RigidBodyComponent>()->onCollisionEnter(ent1);
        }

    }

    void
    CaromScene::manageExitCollisions(b2ContactEvents contactEvents){

        if(!_updatePhysics) return;
        
        for(int i = 0; i < contactEvents.endCount; ++i){
            b2ContactEndTouchEvent* a_exit = contactEvents.endEvents + i;
        
            ecs::entity_t ent1 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->shapeIdA));
            ecs::entity_t ent2 = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->shapeIdB));
        
            ent1->getComponent<ecs::RigidBodyComponent>()->onCollisionExit(ent2);
            ent2->getComponent<ecs::RigidBodyComponent>()->onCollisionExit(ent1);
        }
        
    }

    void
    CaromScene::manageEnterTriggers(b2SensorEvents sensorEvents){

        if(!_updatePhysics) return;

        for(int i = 0; i < sensorEvents.beginCount; ++i){
            b2SensorBeginTouchEvent* a_enter = sensorEvents.beginEvents + i;

            ecs::entity_t sensor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->sensorShapeId));
            ecs::entity_t visitor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_enter->visitorShapeId));

            sensor->getComponent<ecs::RigidBodyComponent>()->onTriggerEnter(visitor);
        }

    }

    void
    CaromScene::manageExitTriggers(b2SensorEvents sensorEvents){

        if(!_updatePhysics) return;

        for(int i = 0; i < sensorEvents.endCount; ++i){
            b2SensorEndTouchEvent* a_exit = sensorEvents.endEvents + i;
        
            ecs::entity_t sensor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->sensorShapeId));
            ecs::entity_t visitor = static_cast<ecs::entity_t>(b2Shape_GetUserData(a_exit->visitorShapeId));
        
            sensor->getComponent<ecs::RigidBodyComponent>()->onTriggerExit(visitor);
        } 

    }

    ScoreContainer* CaromScene::getScoreContainer() {return _scoreContainer;}

    ColorHitManager* CaromScene::getColorHitManager() {return _hitManager; }
}