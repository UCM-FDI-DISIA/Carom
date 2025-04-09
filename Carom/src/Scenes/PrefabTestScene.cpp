#include "PrefabTestScene.h"
#include "JsonEntityParser.h"

PrefabTestScene::PrefabTestScene(Game* g, GameScene* reward) : CaromScene(g, reward){
    init();
}

void PrefabTestScene::init(){
    JsonEntityParser::CreateBallEffect(*this, "../../resources/prefabs/basicBallPrefab.json");
}