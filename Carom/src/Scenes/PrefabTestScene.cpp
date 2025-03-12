#include "PrefabTestScene.h"
#include "JsonEntityParser.h"

PrefabTestScene::PrefabTestScene(Game* myGame){
    game = myGame;
    init();
}

void PrefabTestScene::init(){
    // ecs::JsonEntityParser::Parse(*this, "../../resources/prefabs/examplePrefab.json");
}