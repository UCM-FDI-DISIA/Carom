#include "PauseScene.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "UnpauseComponent.h"
#include "TweenComponent.h"
#include "PhysicsUtils.h"

PauseScene::PauseScene(Game* g, GameScene* scene): GameScene(g){
    _bottomScene = scene;

    

    instantiateInventory();
}

void
PauseScene::instantiateInventory(){

    //fondo del cajon
    entity_t fondo = new Entity(*this, grp::UI);
    b2Vec2 initialPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer_initial_pos").x, sdlutils().height()/2);
    auto tr = addComponent<TransformComponent>(fondo, initialPos);
    addComponent<RenderTextureComponent>(fondo, &sdlutils().images().at("drawer"), renderLayer::GIMMICK, 1);
    auto tween = addComponent<TweenComponent>(fondo);

    //animacion
    b2Vec2 finalPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer").x, sdlutils().height()/2);
    tween->easePosition(finalPos, .5f, tween::EASE_OUT_ELASTIC, false, [=](){
        //UNPAUSE ENTITY
        Entity* unpause = new Entity(*this, grp::PAUSE_UNPAUSE);
        addComponent<UnpauseComponent>(unpause);
    });
    
}

void PauseScene::render(){
    _bottomScene->render();
    GameScene::render();
}