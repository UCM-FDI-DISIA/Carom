#include "PauseScene.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"

PauseScene::PauseScene(Game* g, GameScene* scene): GameScene(g){
    _bottomScene = scene;

    instantiateInventory();
}

void
PauseScene::instantiateInventory(){
    float scale = sdlutils().svgs().at("inventory").at("cajon").width / (float)sdlutils().images().at("fondo").getRect().h;

    entity_t fondo = new Entity(*this, grp::UI);
    auto tr = addComponent<TransformComponent>(fondo, b2Vec2{0,0});
    tr->setRotation(90);
    addComponent<RenderTextureComponent>(fondo, &sdlutils().images().at("fondo"), renderLayer::GIMMICK, scale);
}

void PauseScene::render(){
    _bottomScene->render();
    GameScene::render();
}