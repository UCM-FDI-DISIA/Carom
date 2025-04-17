#include "PauseScene.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "UnpauseComponent.h"
#include "TweenComponent.h"
#include "PhysicsUtils.h"
#include "InventoryManager.h"
#include "FollowComponent.h"

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

    float drawerScale =sdlutils().svgs().at("inventory").at("drawer").height/(float) sdlutils().images().at("drawer").getRect().h;

    addComponent<RenderTextureComponent>(fondo, &sdlutils().images().at("drawer"), renderLayer::GIMMICK, drawerScale);
    auto tween = addComponent<TweenComponent>(fondo);

    //animacion
    b2Vec2 finalPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer").x, sdlutils().height()/2);
    tween->easePosition(finalPos, .5f, tween::EASE_OUT_ELASTIC, false, [=](){
        //UNPAUSE ENTITY
        Entity* unpause = new Entity(*this, grp::PAUSE_UNPAUSE);
        addComponent<UnpauseComponent>(unpause, tween);
    });
    
    float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;

    auto vBalls = InventoryManager::Instance()->getEffectBalls(*this, std::vector<b2Vec2>{});
    for(int i =0; i < InventoryManager::Instance()->MAX_BALLS; i++){
        if(vBalls[i] != nullptr){
            std::string key = "ball_" + std::to_string(i+1);
        
            auto ballPos = sdlutils().svgs().at("inventory").at(key);
            auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");

            b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(ballPos.x - drawerPos.x), PhysicsConverter::pixel2meter(ballPos.y - drawerPos.y)};

            addComponent<FollowComponent>(vBalls[i], fondo, true, false, false, Vector2D(relativeDistance.x, relativeDistance.y));
        }
        
    }
}

void PauseScene::render(){
    _bottomScene->render();
    GameScene::render();
}