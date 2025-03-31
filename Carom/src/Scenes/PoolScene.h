#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"

class ScenesManager;
class RNG_Manager;

namespace ecs{
    class PoolScene: public UIScene {
    protected:
        static constexpr int HOLES = 6;
        enum BallTypes{
                ROUND,
                BOSS
            };

        const float W = 1.6;
        const float H = .7f;
        // Posiciones posibles de agujeros de mesa de pool(por el momento no es exacto).
        std::vector<b2Vec2> _poolPositions = {
            b2Vec2(-W, H), // arriba izquierda.
            b2Vec2(0, H), // arriba centro.
            b2Vec2(W, H), // arriba derecha.
            b2Vec2(-W, -H), // abajo izquierda.
            b2Vec2(0, -H), // abajo centro.
            b2Vec2(W, -H)  // abajo derecha.
        };
        
        RNG_Manager* _rngm; // random manager
        GameScene* _reward; //La recompensa al completar la escena
        b2WorldId _myB2WorldId; //El mundo de box2D

        void generateRndBallsPos(); // para la generación aleatoria de la pos de las bolas.

    public:
        PoolScene(Game* g);
        ~PoolScene();
    };

}
