#include "MainScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"



MainScene::MainScene(State* s, Game* g): GameScene(g){
    setNewState(s);

    createWhiteBall({30, 30}, b2_dynamicBody, 1, 1, 1, 10); // ! tst
}

void // TODO: provisory definition
MainScene::createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    ecs::entity_t e = new ecs::Entity();
    addComponent<ecs::TransformComponent>(e);
    addComponent<ecs::RenderTextureComponent>(e, &sdlutils().images().at("tennis_ball"));
    // std::unique_ptr<ecs::CircleShape> cs = std::make_unique<ecs::CircleShape>(radius);
    ecs::CircleShape *cs = new ecs::CircleShape(radius);
    addComponent<ecs::RigidBodyComponent>(e, b2_dynamicBody, cs, density, friction, restitution);
    // TODO: other components
    e->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({100, 100});
    _entities.push_back(e);
    _entsByGroup[ecs::grp::WHITEBALL].push_back(e);
}

void // TODO: provisory definition
MainScene::createEffectBall(ecs::effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    ecs::entity_t e = new ecs::Entity();
    addComponent<ecs::TransformComponent>(e);
    // TODO: other components
    _entities.push_back(e);
    _entsByGroup[ecs::grp::EFFECTBALLS].push_back(e);
}

void // TODO: provisory definition
MainScene::createTable(/* type */) {
    ecs::entity_t e = new ecs::Entity();
    // TODO: components
    _entities.push_back(e);
    _entsByGroup[ecs::grp::TABLE].push_back(e);
}

void MainScene::setNewState(State* s){
    if (_currentState != nullptr) {
        _currentState->onStateExit();
        delete _currentState;
    }
    _currentState = s;
    _currentState->onStateEnter();
}

State* MainScene::getCurrentState(){ return _currentState;}

MainScene::~MainScene(){
    if(_currentState != nullptr) delete _currentState;
}

void MainScene::update(){
    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    _currentState->update();
    GameScene::update();
}