#include "GameScene.h"

GameScene::GameScene(Game* game): game(game){}

void GameScene::addObject(Entity* entity){
    entities.push_back(entity);
}

