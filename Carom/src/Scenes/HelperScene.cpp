#include "HelperScene.h"

HelperScene::HelperScene(Game* g, std::shared_ptr<GameScene> scene): GameScene(g){
    _bottomScene = scene;
}

void HelperScene::update(){
    _bottomScene->update();
    GameScene::update();
}

void HelperScene::render(){
    _bottomScene->render();
    GameScene::render();
}

void HelperScene::handleEvent(){
    _bottomScene->handleEvent();
    GameScene::handleEvent();
}