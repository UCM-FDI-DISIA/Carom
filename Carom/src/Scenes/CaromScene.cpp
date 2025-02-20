#include "CaromScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"

CaromScene::CaromScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward) 
{
    setNewState(s);
}

void // TODO: provisory definition
CaromScene::createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    ecs::entity_t e = new ecs::Entity(*this);
    addComponent<ecs::TransformComponent>(e, pos);

    addComponent<ecs::RenderTextureComponent>(e, &sdlutils().images().at("tennis_ball"));

    ecs::CircleShape *cs = new ecs::CircleShape(radius);
    addComponent<ecs::RigidBodyComponent>(e, b2_dynamicBody, cs, density, friction, restitution);

    // TODO: other components
    // e->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({100, 100});
    _entities.push_back(e);
    _entsByGroup[ecs::grp::WHITEBALL].push_back(e);
}

void // TODO: provisory definition
CaromScene::createEffectBall(ecs::effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    ecs::entity_t e = new ecs::Entity(*this);
    addComponent<ecs::TransformComponent>(e, pos);
    // TODO: other components
    _entities.push_back(e);
    _entsByGroup[ecs::grp::EFFECTBALLS].push_back(e);
}

void // TODO: provisory definition
CaromScene::createTable(/* type */) {
    ecs::entity_t e = new ecs::Entity(*this);
    // TODO: components
    _entities.push_back(e);
    _entsByGroup[ecs::grp::TABLE].push_back(e);
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
}

void CaromScene::update(){
    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    _currentState->update();
    GameScene::update();
}