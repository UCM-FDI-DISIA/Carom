#include "PrefabTestScene.h"
#include "JsonEntityParser.h"

PrefabTestScene::PrefabTestScene(Game* myGame){
    game = myGame;
    init();
}

void PrefabTestScene::init(){
    JsonEntityParser::Parse(*this, "../../resources/prefabs/examplePrefab.json");
}