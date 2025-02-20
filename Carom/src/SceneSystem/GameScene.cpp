#include <SDLUtils.h>
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "GameScene.h"
#include "../Game.h"

namespace ecs{

GameScene::GameScene(Game* game): game(game){}

GameScene::~GameScene(){};

// TODO: componentes Transform físico y normal
// Creates a table composed by 3 entities for textures and 4 entities that are the colliders of each side of the table.
// The table is not an entity per se, is represented by a group of entities.
// Those entities are grouped here -> _entsByGroup[grp::TABLE]
void GameScene::createTable(Texture* tx_marco, Texture* tx_sombraMarco, Texture* tx_suelo){
    // Entidad marco
    entity_t e_marco = new Entity(*this);
    Vector2D pos_marco = {};
    addComponent<TransformComponent>(e_marco, pos_marco);
    addComponent<RenderComponent>(e_marco, tx_marco);
    _entsByGroup[grp::TABLE].push_back(e_marco);
    _entities.push_back(e_marco);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this);
    Vector2D pos_sombraMarco = {};
    addComponent<TransformComponent>(e_sombraMarco, pos_sombraMarco);
    addComponent<RenderComponent>(e_sombraMarco, tx_sombraMarco);
    _entsByGroup[grp::TABLE].push_back(e_sombraMarco);
    _entities.push_back(e_sombraMarco);

    // Entidad suelo
    entity_t e_suelo = new Entity(*this);
    Vector2D pos_suelo = {};
    addComponent<TransformComponent>(e_suelo, pos_suelo);
    addComponent<RenderComponent>(e_suelo, tx_suelo);
    _entsByGroup[grp::TABLE].push_back(e_suelo);
    _entities.push_back(e_suelo);

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

