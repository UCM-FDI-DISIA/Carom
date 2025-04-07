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
//#include "ScoreContainer.h"
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
    generateTable();
    generateRndBallsPos();
}

PoolScene::~PoolScene()
{
    delete _rngm;
}

void PoolScene::generateRndBallsPos()
{
    /*
    ESTE REFACTOR NO VA 
    // Entre 0 y posiciones-1 elige un indice para que sea el boss.
    int a_bossPosition = _rngm->randomRange(0, HOLES);
    std::cout << "Boss hole: " << a_bossPosition << std::endl;

    // coloca los agujeros de partida
    for(int i = 0; i < HOLES; i++){

        b2Vec2 pos = _poolPositions[i];

        
        NullState* state = new NullState(nullptr);

        // !!! CREA BOSSSCENE(CAMBIAR).
        UIScene* rewardScene = new RewardScene(game);
        CowboyPoolScene *ms = new CowboyPoolScene(state, game, rewardScene, true); // ! tst  

        if(i == a_bossPosition){ // --- POSICION BOSS.
            entity_t e = createSceneButton(pos.x, pos.y, ms, grp::POOL_HOLE, renderLayer::POOL_HOLE, "hole", 0.2f);
        }
        else{ // --- POSICION COLORES.
            entity_t e = createSceneButton(pos.x, pos.y, ms, grp::POOL_HOLE, renderLayer::POOL_HOLE, "hole", 0.2f);
        }
    }
    */
    // Entre 0 y posiciones-1 elige un indice para que sea el boss.
    int a_bossPosition = _rngm->randomRange(0, HOLES);
    std::cout << "Boss hole: " << a_bossPosition << std::endl;

    // coloca los agujeros de partida
    for(int i = 0; i < HOLES; i++){

        // genera el agujero.
        entity_t e = generateHole(i);

        if(i == a_bossPosition){ // --- POSICION BOSS.
            //createSceneButton(pos.x, pos.y, ms, grp::POOL_HOLE, renderLayer::POOL_HOLE, "hole", 0.2f)
            
            e->getComponent<Button>()->setOnClick([this](){
                
                NullState* state = new NullState(nullptr);

                // !!! CREA BOSSSCENE(CAMBIAR).
                UIScene* rewardScene = new RewardScene(game);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, rewardScene, true); // ! tst  
                game->getScenesManager()->pushScene(ms);
            });
        }
        else{ // --- POSICION COLORES.
            e->getComponent<Button>()->setOnClick([this](){
                
                NullState* state = new NullState(nullptr);

                // !!! CREA COWBOYPOOLSCENE(CAMBIAR).
                UIScene* rewardScene = new RewardScene(game);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, rewardScene, true); // ! tst  
                game->getScenesManager()->pushScene(ms);
            });
        }

        
    }

    generateTableBackground();

}

void PoolScene::generateTable()
{
    // Marco de la mesa.
    entity_t e = new Entity(*this, grp::TABLE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("mesa_marco").x,
        *&sdlutils().svgs().at("pool").at("mesa_marco").y
    );

    float scale = float(sdlutils().svgs().at("pool").at("mesa_marco").width) / float(sdlutils().images().at("marco2").width());


    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, scale);

    // Sombra de la mesa.
    entity_t e1 = new Entity(*this, grp::TABLE);

    b2Vec2 pos1 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("mesa_sombra").x,
        *&sdlutils().svgs().at("pool").at("mesa_sombra").y
    );

    addComponent<TransformComponent>(e1, pos1);
    addComponent<RenderTextureComponent>(e1, &sdlutils().images().at("mesa1_sombra"), renderLayer::TABLE_SHADOW, scale);
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

void PoolScene::generateTableBackground()
{
    // fondo mesa.
    entity_t e = new Entity(*this, grp::TABLE_BACKGROUND);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("fondo_mesa").x,
        *&sdlutils().svgs().at("pool").at("fondo_mesa").y
    );

    float scale = float(sdlutils().svgs().at("pool").at("fondo_mesa").width) / float(sdlutils().images().at("fondo_verde").width());


    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("fondo_verde"), renderLayer::TABLE_BACKGOUND, scale);
}
