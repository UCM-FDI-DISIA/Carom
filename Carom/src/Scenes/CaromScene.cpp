#include "CaromScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"

CaromScene::CaromScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward) 
{
    setNewState(s);

    createWhiteBall(Vector2D(-3.5f, 0.0), b2_dynamicBody, 1, 1, 1, 1, 10); // ! tst
    getEntitiesOfGroup(ecs::grp::WHITEBALL)[0]->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({5.0f, 0.0f});
    createWhiteBall(Vector2D(1, 0), b2_dynamicBody, 2, 1, 1, 1, 1); // ! tst
    getEntitiesOfGroup(ecs::grp::WHITEBALL)[1]->getComponent<ecs::RigidBodyComponent>()->applyImpulseToCenter({-1.0f, 1.0f});
}

void // TODO: provisory definition, add components
CaromScene::createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius, int capa) {
    ecs::entity_t e = new ecs::Entity(*this);
    addComponent<ecs::TransformComponent>(e, pos);
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e);
    addComponent<ecs::RenderTextureComponent>(e, &sdlutils().images().at("tennis_ball"), capa);

    ecs::CircleShape *cs = new ecs::CircleShape(radius);
    addComponent<ecs::RigidBodyComponent>(e, b2_dynamicBody, cs, density, friction, restitution);

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
}

void CaromScene::update(){
    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    _currentState->update();
    GameScene::update();
}