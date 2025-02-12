#include "GameScene.h"

GameScene::GameScene(Game* game): game(game){}

void GameScene::addObject(Entity* entity){
    entities.push_back(entity);
}

void GameScene::render() const{
    for (auto entity : entities) {
        entity.render();
    }
}

void GameScene::update() const{
    for (auto entity : entities) {
        entity.update();
    }
}

void GameScene::handleEvent() const{
    for (auto entity : entities) {
        entity.handleEvent();
    }
}

void GameScene::clear(){
     for (auto entity : entities) {
        delete entity;
    }
}