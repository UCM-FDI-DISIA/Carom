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
//#include "ScoreContainer.h"
//#include "StickInputComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>

namespace ecs{

    PoolScene::PoolScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward) 
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

    void PoolScene::setNewState(State *s)
    {
        // if (_currentState != nullptr) {
        //     _currentState->onStateExit();
        //     delete _currentState;
        // }
        // _currentState = s;
        // _currentState->onStateEnter();
    }

    void PoolScene::generateRndBallsPos()
    {
        entity_t table = new ecs::Entity(*this, grp::DEFAULT);
        b2Vec2 pos(0,0);
        addComponent<TransformComponent>(table, pos);
        addComponent<RenderTextureComponent>(table, &sdlutils().images().at("mesa1"), 4, 1);

        table = new ecs::Entity(*this, grp::DEFAULT);
        addComponent<TransformComponent>(table, pos);
        addComponent<RenderTextureComponent>(table, &sdlutils().images().at("fondo"), 3, 1);
        
        // Entre 0 y posiciones-1 elige un indice para que sea el boss.
        int a_bossPosition = _rngm->randomRange(0, HOLES);

        // coloca los tipos.
        for(int i = 0; i < HOLES; i++){

            // crea una ball.
            entity_t e = new ecs::Entity(*this, grp::POOL_HOLE);
            b2Vec2 pos = _poolPositions[i];
            addComponent<TransformComponent>(e, pos);
            addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), 5, 0.2f);

            ecs::Button::TextureButton rButton = ecs::Button::TextureButton();
            addComponent<ecs::Button>(e, rButton);


            if(i == a_bossPosition){ // --- POSICION BOSS.
                e->getComponent<ecs::Button>()->setOnClick([this](){
                    std::cout << "Carga escena Boss" << std::endl;
                    NullState* state = new NullState(nullptr);
                    ecs::CowboyPoolScene *ms = new ecs::CowboyPoolScene(state, game, nullptr, true); // ! tst  
                    game->getScenesManager()->pushScene(ms);
                });
            }
            else{ // --- POSICION COLORES.
                e->getComponent<ecs::Button>()->setOnClick([this](){
                    std::cout << "Carga escena Carom" << std::endl;
                    NullState* state = new NullState(nullptr);
                    ecs::CowboyPoolScene *ms = new ecs::CowboyPoolScene(state, game, nullptr, false); // ! tst  
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
