#include <SDLUtils.h>

#include "GameScene.h"
#include "Camera.h"

namespace ecs{

GameScene::GameScene(Game* game): game(game), _worldCamera(0,0), _UICamera(0,0){ }

GameScene::~GameScene(){};

void GameScene::render(){
    for (auto entity : _entities) {
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

