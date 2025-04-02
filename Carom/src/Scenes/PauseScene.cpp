#include "PauseScene.h"

PauseScene::PauseScene(Game* g, GameScene* scene): GameScene(g){
    _bottomScene = scene;
}

void PauseScene::render(){
    GameScene::render();
    _bottomScene->render();
}