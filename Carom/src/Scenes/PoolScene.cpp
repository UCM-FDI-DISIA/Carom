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
//#include "StickInputComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>

namespace ecs{

    PoolScene::PoolScene(Game* g) : UIScene(g)
    {
        _rngm = new RNG_Manager();

        // Create table with texture and colliders
        createBackground("suelo");
        generateRndBallsPos();
    }

    PoolScene::~PoolScene()
    {
        delete _rngm;
    }

    void PoolScene::generateRndBallsPos()
    {
        entity_t table = new ecs::Entity(*this, grp::DEFAULT);
        b2Vec2 pos(0,0);
        addComponent<TransformComponent>(table, pos);
        addComponent<RenderTextureComponent>(table, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, 1);

        table = new ecs::Entity(*this, grp::DEFAULT);
        addComponent<TransformComponent>(table, pos);
        addComponent<RenderTextureComponent>(table, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, 1, SDL_Color{0, 150, 80, 255});
        
        // Entre 0 y posiciones-1 elige un indice para que sea el boss.
        int a_bossPosition = _rngm->randomRange(0, HOLES);
        std::cout << "Boss hole: " << a_bossPosition << std::endl;

        // coloca los agujeros de partida
        for(int i = 0; i < HOLES; i++){

            entity_t e = new ecs::Entity(*this, grp::POOL_HOLE);
            b2Vec2 pos = _poolPositions[i];
            addComponent<TransformComponent>(e, pos);
            addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, 0.2f);

            ecs::Button::TextureButton rButton = ecs::Button::TextureButton();
            addComponent<ecs::Button>(e, rButton);

            

            if(i == a_bossPosition){ // --- POSICION BOSS.
                //createSceneButton(pos.x, pos.y, ms, ecs::grp::POOL_HOLE, ecs::renderLayer::POOL_HOLE, "hole", 0.2f)
               
                e->getComponent<ecs::Button>()->setOnClick([this](){
                   
                    NullState* state = new NullState(nullptr);

                    // !!! CREA BOSSSCENE(CAMBIAR).
                    ecs::UIScene* rewardScene = new ecs::RewardScene(game);
                    ecs::CowboyPoolScene *ms = new ecs::CowboyPoolScene(state, game, rewardScene, true); // ! tst  
                    game->getScenesManager()->pushScene(ms);
                });
            }
            else{ // --- POSICION COLORES.
                e->getComponent<ecs::Button>()->setOnClick([this](){
                   
                    NullState* state = new NullState(nullptr);

                    // !!! CREA COWBOYPOOLSCENE(CAMBIAR).
                    ecs::UIScene* rewardScene = new ecs::RewardScene(game);
                    ecs::CowboyPoolScene *ms = new ecs::CowboyPoolScene(state, game, rewardScene, true); // ! tst  
                    game->getScenesManager()->pushScene(ms);
                });
            }

            /* ESTO NO FUNCIONA DA ERROR PERO SE NECESITA.
            ecs::entity_t e = new ecs::Entity(*this);
            _entities.push_back(e); // nota: _entiites heredado
            */
        }

    }
}
