#include "PrefabTestScene.h"
#include "JsonEntityParser.h"

PrefabTestScene::PrefabTestScene(State* state, Game* g, GameScene* reward) : CaromScene(state, g, reward){
    init();
}

void PrefabTestScene::init(){
    JsonEntityParser::CreateBallEffect(*this, "../../resources/prefabs/basicBallPrefab.json");
}