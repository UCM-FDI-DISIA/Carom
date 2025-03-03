#include "PoolScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
//#include "ScoreContainer.h"
//#include "StickInputComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>

namespace ecs{

    PoolScene::PoolScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward) 
    {
        _rngm = new RNG_Manager();
    }

    PoolScene::~PoolScene()
    {
        delete _rngm;
    }

    void PoolScene::generateRndBallsPos()
    {
        // para porderlo meter en getRandomItems hay que hacer esto.
        std::vector<RandomItem<Vector2D>> a_fixedPoolPositions;
        for(auto p : _poolPositions){
            a_fixedPoolPositions.emplace_back(RandomItem<Vector2D>(p, 0));
        }

        // pueden salir entre 2 y 6 espacios llenos en la mesa de pool, ni mas ni menos.
        // el caso de 2 (minimo) seria de el boss y una sala nada mas.
        int nBalls = _rngm->randomRange(2, 7); // nota: creo q se hace [x, y) el randomRange.

        // De las posiciones disponibles para que salga elige un numero entre 2 y 6 sin reemplazamiento (para no repetir posiciones).
        std::vector<Vector2D> a_finalPositions = _rngm->getRandomItems(a_fixedPoolPositions, nBalls, false);

        // Entre 0 y posiciones-1 elige un indice para que sea el boss.
        int a_bossPosition = _rngm->randomRange(0, a_finalPositions.size());

        // coloca los tipos.
        for(int i = 0; i < a_finalPositions.size(); i++){

            // crea una ball.
            PoolBall a_ball;
            
            if(i == a_bossPosition){ // --- POSICION BOSS.
                a_ball.position = a_finalPositions[i]; //pos.
                a_ball.type = _ballTypes[1]; // tipo.
                auto a_bossEntity = _entsByGroup[ecs::grp::POOLBOSS]; // grupo (_entsbygroup heredado)
            }
            else{ // --- POSICION COLORES.
                a_ball.position = a_finalPositions[i]; //pos.
                a_ball.type = _ballTypes[0]; //tipo.
                auto a_colorEntity = _entsByGroup[ecs::grp::POOLBALLS]; // grupo (_entsbygroup heredado)
            }

            /* ESTO NO FUNCIONA DA ERROR PERO SE NECESITA.
            ecs::entity_t e = new ecs::Entity(*this);
            _entities.push_back(e); // nota: _entiites heredado
            */
        }

    }
}
