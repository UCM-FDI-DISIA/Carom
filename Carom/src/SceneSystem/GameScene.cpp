#include <SDLUtils.h>
#include <algorithm>
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"

#include "GameScene.h"
#include "../Game.h"
#include "Camera.h"

namespace ecs{

GameScene::GameScene(Game* game): game(game), _worldCamera(0,0), _UICamera(0,0){ }

GameScene::~GameScene(){};

// TODO: componentes Transform físico y normal
// Creates a table composed by 3 entities for textures and 4 entities that are the colliders of each side of the table.
// The table is not an entity per se, is represented by a group of entities.
// Those entities are grouped here -> _entsByGroup[grp::TABLE]
void
GameScene::createTable(){
    
    // Entidad marco
    entity_t e_marco = new Entity(*this);
    // Vector2D pos = {288, 81};
    // Vector2D pos = {PhysicsConverter::pixel2meter(288), PhysicsConverter::pixel2meter(81)};
    Vector2D pos = {0,0};
    // Vector2D pos = {10,10};


    Vector2D scale = {0.85f, 0.85f};
    addComponent<TransformComponent>(e_marco, pos);
    // e_marco->getComponent<TransformComponent>()->setScale
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e_marco);
    addComponent<RenderTextureComponent>(e_marco, &sdlutils().images().at("marco2"), 2);
    _entsByGroup[grp::TABLE].push_back(e_marco);
    _entities.push_back(e_marco);

    // Entidad suelo
    entity_t e_suelo = new Entity(*this);
    addComponent<TransformComponent>(e_suelo, pos);
    // e_suelo->getComponent<TransformComponent>();
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e_suelo);
    addComponent<RenderTextureComponent>(e_suelo, &sdlutils().images().at("fondo"), 1);
    _entsByGroup[grp::TABLE].push_back(e_suelo);
    _entities.push_back(e_suelo);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this);
    addComponent<TransformComponent>(e_sombraMarco, pos);
    // e_sombraMarco->getComponent<TransformComponent>();
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e_sombraMarco);
    addComponent<RenderTextureComponent>(e_sombraMarco, &sdlutils().images().at("mesa1_sombra"), 0);
    _entsByGroup[grp::TABLE].push_back(e_sombraMarco);
    _entities.push_back(e_sombraMarco);

    //---- BODIES ----//
    // Create an entity for each cushion (border) of the table
    for (int i = 0; i < game->nCushions; ++i){
        entity_t e_coll = new Entity(*this);
        Vector2D pos_coll = {};
        addComponent<TransformComponent>(e_coll, pos_coll); // TODO: cambiar a transform físico
        _entsByGroup[grp::TABLE].push_back(e_coll);
        _entities.push_back(e_coll);
    }

}

void GameScene::sortRenderOrder(){
    std::sort(_entsRenderable.begin(), _entsRenderable.end(), [](entity_t a, entity_t b) {
        return a->getComponent<RenderTextureComponent>()->renderOrder < b->getComponent<RenderTextureComponent>()->renderOrder;
    });
}

void GameScene::render(){
    for (auto entity : _entsRenderable) {
        entity->render(&_worldCamera);
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

Camera* GameScene::getWorldCamera(){
    return &_worldCamera;
}

Camera* GameScene::getUICamera() {
    return &_UICamera;
}

void GameScene::setWorldCamera(b2Vec2 pos){
    _worldCamera = Camera(pos.x, pos.y);
}

void GameScene::setUICamera(b2Vec2 pos){
    _UICamera = Camera(pos.x, pos.y);
}
};

