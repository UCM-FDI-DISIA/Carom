#include "PrefabTestScene.h"
#include "JsonEntityParser.h"

PrefabTestScene::PrefabTestScene(Game* game){
    _game = game;
    init();
}

void PrefabTestScene::init(){
    JsonEntityParser::Parse(*this, "../../resources/prefabs/examplePrefab.json");
}