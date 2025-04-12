#include "PoolScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "CaromScene.h"
#include "CowboyPoolScene.h"

#include "RewardScene.h"
#include "StickInputComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>


PoolScene::PoolScene(Game* g) : UIScene(g)
{
    createPauseEntity();
    _rngm = new RNG_Manager();

    // Create table with texture and colliders
    createBackground("suelo");
    createTable();
    generateRndBallsPos();
}

PoolScene::~PoolScene()
{
    delete _rngm;
}

void PoolScene::generateRndBallsPos()
{
    // Entre 0 y posiciones-1 elige un indice para que sea el boss.
    int a_bossPosition = _rngm->randomRange(0, HOLES);
    std::cout << "Boss hole: " << a_bossPosition << std::endl;

    // coloca los agujeros de partida
    for(int i = 0; i < HOLES; i++){

        // genera el agujero.
        entity_t e = generateHole(i);

        if(i == a_bossPosition){ // --- POSICION BOSS.
            
            e->getComponent<Button>()->setOnClick([this](){
                // !!! CREA BOSSSCENE(CAMBIAR)
                NullState* state = new NullState(nullptr);
                UIScene* rewardScene = new RewardScene(game);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, rewardScene, true); // ! tst  
                game->getScenesManager()->pushScene(ms);
            });
        }
        else{ // --- POSICION COLORES.
            e->getComponent<Button>()->setOnClick([this](){
                // !!! CREA COWBOYPOOLSCENE
                NullState* state = new NullState(nullptr);
                UIScene* rewardScene = new RewardScene(game);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, rewardScene, true); // ! tst  
                game->getScenesManager()->pushScene(ms);
            });
        }
    }
}

entity_t PoolScene::generateHole(int i)
{
    // agujero.
    entity_t e = new Entity(*this, grp::POOL_HOLE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).x + 145, // mirar lo de +145 y +160 pq tiene q hacerse si en svg esta colocao??
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).y + 160
    );

    float scale = float(sdlutils().svgs().at("pool").at("hole 0").width) / float(sdlutils().images().at("hole").width());

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    return e;
}