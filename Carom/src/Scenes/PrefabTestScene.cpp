#include "PrefabTestScene.h"
#include "JsonEntityParser.h"

PrefabTestScene::PrefabTestScene(State* state, Game* g) : CaromScene(state, g){
    init();
}

void PrefabTestScene::init(){
    JsonEntityParser::CreateBallEffect(*this, "../../resources/prefabs/basicBallPrefab.json");
}