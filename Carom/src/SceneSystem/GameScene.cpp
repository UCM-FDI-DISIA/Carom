#include <SDLUtils.h>

#include "GameScene.h"

namespace ecs{

GameScene::GameScene(Game* game): _game(game){}

GameScene::~GameScene(){};

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

