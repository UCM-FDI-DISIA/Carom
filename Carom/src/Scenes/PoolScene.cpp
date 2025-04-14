#include "PoolScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RewardInfoDisplayComponent.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "CaromScene.h"
#include "RewardScene.h"
#include "CowboyPoolScene.h"

#include "RewardScene.h"
//#include "ScoreContainer.h"
#include "StickInputComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>


using body_t = RewardInfoDisplayComponent::Body;

PoolScene::PoolScene(Game* g) : UIScene(g)
{
    createPauseEntity();
    _rngm = new RNG_Manager();

    // Create table with texture and colliders
    createBackground("suelo");
    createTable();
    generateMatchHoles();
    generateFloorRewards();
}

PoolScene::~PoolScene()
{
    delete _rngm;
}

void PoolScene::generateMatchHoles()
{
    // Entre 0 y posiciones-1 elige un indice para que sea el boss.
    _bossHole = _rngm->randomRange(0, HOLES);
    #ifdef _DEBUG
    std::cout << "Boss hole: " << _bossHole << std::endl;
    #endif

    // coloca los agujeros de partida
    for(int i = 0; i < HOLES; i++){

        // genera el agujero.
        entity_t hole = generateHole(i);

        auto button = hole->getComponent<Button>();

        if(i == _bossHole){ // --- POSICION BOSS.
            //createSceneButton(pos.x, pos.y, ms, grp::POOL_HOLE, renderLayer::POOL_HOLE, "hole", 0.2f)
            
            button->setOnClick([this](){
                
                NullState* state = new NullState(nullptr);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, true); // ! tst  
                
                RewardScene* rs = new RewardScene(game); // TODO: Escena de recompensas de boss (pasar de piso, bolas de la mesa)
                
                game->getScenesManager()->pushScene(rs);
                game->getScenesManager()->pushScene(ms);
            });
        }
        else{ // --- POSICION COLORES.
            button->setOnClick([this](){
                
                NullState* state = new NullState(nullptr);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, false); // ! tst  
                
                RewardScene* rs = new RewardScene(game);

                game->getScenesManager()->pushScene(rs);
                game->getScenesManager()->pushScene(ms);
            });
        }

        button->setOnHover([this, i]() {
            #ifdef _DEBUG
            std::cout << "Hovering pool hole " << i << std::endl; 
            #endif

            showReward(i);
        });

        button->setOnExit([this, i]() {
            #ifdef _DEBUG
            std::cout << "Exiting pool hole " << i << std::endl; 
            #endif

            hideReward(i);
        });
    }

}

entity_t PoolScene::generateHole(int i)
{
    // agujero.
    entity_t e = new Entity(*this, grp::POOL_HOLE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).x,
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).y
    );

    float scale = float(sdlutils().svgs().at("pool").at("hole 0").width) / float(sdlutils().images().at("hole").width());

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    return e;
}

void
PoolScene::loadRewards() {
    // TODO: parse all rewards from JSON

    // PROVISIONAL, para testear
    for(int i = 0; i < HOLES; i++)
        _rewards.push_back(RandomItem(Reward(Reward::CAULDRON, Reward::Perma()), 1.0f));
}


void
PoolScene::generateFloorRewards() {
    // Generar array de todas las recompensas a partir del JSON
    loadRewards();

    _floorRewards = _rngm->getRandomItems(_rewards, HOLES, false);
    
    // Boss match does not have a reward (default reward)
    _floorRewards[_bossHole] = Reward();

    createRewardInfo();
}

void
PoolScene::createRewardInfo() {
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("pool").at("box_0").width) / texture->width();

    for(int i = 0; i < HOLES; ++i) {
        description = new Entity(*this, grp::REWARD_INFO_BG);

        auto svgElem = *&sdlutils().svgs().at("pool").at("box_" + std::to_string(i));
        pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale);

        description->deactivate();

        // Añadir texto de recompensa / TODO: texto de partida de boss
        // en función de _floorRewards[i]
        description = new Entity(*this, grp::REWARD_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<RewardInfoDisplayComponent>(description, renderLayer::UI, 
                body_t{"Recompensas de partida", "Bocalupo-Regular48", {255, 255, 255, 255}, scale*1.5f},
                body_t{"Instant 1", "Aladin-Regular48", {255,255,255,255}, scale*1.5f},
                body_t{"Recompensa instantánea", "Aladin-Regular24", {255, 255, 255, 150}, scale*2.f},
                body_t{"Lore ipsum dolor sit amer bla bla bla descripcion super larga para ver si coge varias lineas", 
                        "Aladin-Regular24", {255,255,255,255}, scale*2.f},
                texture->width() - 50
                , -texture->width()/2 * scale + 15, -texture->height()/2 * scale + 35
                // , -PhysicsConverter::pixel2meter(texture->width()/2), -PhysicsConverter::pixel2meter(texture->height()/2)
            );
        description->deactivate();
    }
}

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
}