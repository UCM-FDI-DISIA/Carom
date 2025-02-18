#include <SDLUtils.h>

#include "GameScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"

namespace ecs{

GameScene::GameScene(Game* game): game(game){}

GameScene::~GameScene(){};

// ! doing

void // TODO
GameScene::createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    entity_t e = new Entity();
    addComponent<TransformComponent>(e);
    // TODO: other components
    _entities.push_back(e);
    _entsByGroup[grp::WHITEBALL].push_back(e);
}

void // TODO
GameScene::createEffectBall(effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    entity_t e = new Entity();
    addComponent<TransformComponent>(e);
    // TODO: other components
    _entities.push_back(e);
    _entsByGroup[grp::EFFECTBALLS].push_back(e);
}

void // TODO
GameScene::createTable(/* type */) {
    entity_t e = new Entity();
    // TODO: components
    _entities.push_back(e);
    _entsByGroup[grp::TABLE].push_back(e);
}

//  ! doing

void GameScene::render(){
    for (auto entity : _entities) {
        entity->render();
    }
}

void GameScene::update(){
    for (Entity* entity : _entities) {
        entity->update();
    }
}

void GameScene::handleEvent(){
    for (auto entity : _entities) {
        entity->handleEvents();
    }
}

void GameScene::clear(){
     for (auto entity : _entities) {
        delete entity;
    }
}
};

