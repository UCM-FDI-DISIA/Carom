#include "GameScene.h"
#include "EntityManager.h"

namespace ecs{

GameScene::GameScene(Game* game): game(game){
    _enttmngr = new EntityManager(&entities);
}

GameScene::~GameScene(){};

// void GameScene::addObject(Entity* entity){
//     entities.push_back(entity);
// }

void GameScene::render(){
    for (auto entity : entities) {
        entity->render();
    }
}

void GameScene::update(){
    for (Entity* entity : entities) {
        entity->update();
    }
}

void GameScene::handleEvent(){
    for (auto entity : entities) {
        entity->handleEvents();
    }
}

void GameScene::clear(){
     for (auto entity : entities) {
        delete entity;
    }
}
};

