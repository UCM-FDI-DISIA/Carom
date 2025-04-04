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

        entity_t e = new Entity(*this, grp::POOL_HOLE);
        b2Vec2 pos = _poolPositions[i];
        addComponent<TransformComponent>(e, pos);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, 0.2f);

        Button::TextureButton rButton = Button::TextureButton();
        addComponent<Button>(e, rButton);

        

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

        /* ESTO NO FUNCIONA DA ERROR PERO SE NECESITA.
        entity_t e = new Entity(*this);
        _entities.push_back(e); // nota: _entiites heredado
        */
    }

}

void PoolScene::generateTable()
{
    entity_t table = new Entity(*this, grp::DEFAULT);
    b2Vec2 pos(0,0);
    addComponent<TransformComponent>(table, pos);
    addComponent<RenderTextureComponent>(table, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, 1);

    table = new Entity(*this, grp::DEFAULT);
    addComponent<TransformComponent>(table, pos);
    addComponent<RenderTextureComponent>(table, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, 1, SDL_Color{0, 150, 80, 255});

    /*// !---- TEXTURES ----//
    // Set scale (same for all)
    float svgSize = *&sdlutils().svgs().at("pool").at("mesa_marco").width;
    float textureSize = sdlutils().images().at("mesa1").width();
    float scale = svgSize/textureSize;

    // Entidad marco
    entity_t e_marco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_m = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("pool").at("mesa_marco").x, *&sdlutils().svgs().at("pool").at("mesa_marco").y);
    addComponent<TransformComponent>(e_marco, pos_m);
    addComponent<RenderTextureComponent>(e_marco, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, scale);

    // Entidad suelo
    entity_t e_fondo = new Entity(*this, grp::TABLE_BACKGROUND);
    b2Vec2 pos_f = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("pool").at("fondo_mesa").x, *&sdlutils().svgs().at("pool").at("fondo_mesa").y);
    addComponent<TransformComponent>(e_fondo, pos_f);
    addComponent<RenderTextureComponent>(e_fondo, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, scale);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_s = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("pool").at("mesa_sombra").x, *&sdlutils().svgs().at("pool").at("mesa_sombra").y);
    addComponent<TransformComponent>(e_sombraMarco, b2Vec2{pos_s.x - 0.2f, pos_s.y - 0.2f});
    addComponent<RenderTextureComponent>(e_sombraMarco, &sdlutils().images().at("mesa1_sombra"), renderLayer::TABLE_SHADOW, scale);*/
}
