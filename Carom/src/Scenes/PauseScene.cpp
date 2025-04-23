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
#include "RewardInfoDisplayComponent.h"

using body_t = RewardInfoDisplayComponent::Body;

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

    //auto vBalls = InventoryManager::Instance()->getEffectBalls();
    for(int i =0; i < 6; i++){
        std::string key = "ball_" + std::to_string(i+1);
        entity_t ball = new Entity(*this, grp::UI);
        addComponent<TransformComponent>(ball, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ball, &sdlutils().images().at("bola_blanca"), 100, ballScale);
        
        auto ballPos = sdlutils().svgs().at("inventory").at(key);
        auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");

        b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(ballPos.x - drawerPos.x), PhysicsConverter::pixel2meter(ballPos.y - drawerPos.y)};

        addComponent<FollowComponent>(ball, fondo, true, false, false, Vector2D(relativeDistance.x, relativeDistance.y));
    }

    createBallInfo();
}

void
PauseScene::createBallInfo() {
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("inventory_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

    // Cargamos primero las bolas
    for(int i = 1; i <= InventoryManager::Instance()->getEffectBalls().size(); ++i) {
        // FONDO
        description = new Entity(*this, grp::BALL_INFO_BG);

        auto svgElem = *&sdlutils().svgs().at("inventory").at("ball_Info_" + std::to_string(i));
        pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale);

        //description->deactivate(); // * Temporalmente

        // TEXTO
        // Añadir texto de recompensa / TODO: texto de partida de boss
        // en función de _floorRewards[i]
        description = new Entity(*this, grp::BALL_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<RewardInfoDisplayComponent>(description, renderLayer::UI, 
                body_t{"Recompensas de partida", "Bocalupo-Regular48", {255, 255, 255, 255}, scale*1.5f},
                body_t{"Instant 1", "Aladin-Regular48", {255,255,255,255}, scale*1.5f},
                body_t{"Recompensa instantánea", "Aladin-Regular24", {255, 255, 255, 150}, scale*2.f},
                body_t{"Lore ipsum dolor sit amer bla bla bla descripcion super larga para ver si coge varias lineas", 
                        "Aladin-Regular24", {255,255,255,255}, scale*2.f}
                , texture->width() * scale - 25
                , -texture->width()/2 * scale + 15, -texture->height()/2 * scale + 35
            );
        //description->deactivate(); // * Temporalmente
    }
}
/*
void
PoolScene::showReward(int i) {
    assert(i < HOLES);

    auto descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->activate();
}

void
PoolScene::hideReward(int i) {
    assert(i < HOLES);

    auto descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->deactivate();
}*/

void PauseScene::render(){
    _bottomScene->render();
    GameScene::render();
}