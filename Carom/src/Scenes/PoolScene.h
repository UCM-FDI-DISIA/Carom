#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"

class ScenesManager;
class RNG_Manager;
class Vector2D;


namespace ecs{
    class PoolScene: public GameScene {
    protected:
        struct PoolBall{
            Vector2D position;
            std::string type;
        };
        
        RNG_Manager* _rngm; // random manager
        GameScene* _reward; //La recompensa al completar la escena
        void generateRndBallsPos(); // para la generación aleatoria de la pos de las bolas.

        // vector de bolas.
        std::vector<PoolBall> _balls;

        // Posiciones posibles de agujeros de mesa de pool(por el momento no es exacto).
        std::vector<Vector2D> _poolPositions = {
            Vector2D(25, 100), // arriba izquierda.
            Vector2D(50, 100), // arriba centro.
            Vector2D(75, 100), // arriba derecha.
            Vector2D(25, 300), // abajo izquierda.
            Vector2D(50, 300), // abajo centro.
            Vector2D(75, 300)  // abajo derecha.
        };

        // tipos de bolas.
        std::vector<std::string> _ballTypes = {
            "color",
            "boss"
        }; // nota: luego cuando tengamos mas juego seria conveniente cambiar "color" por diferentes tipos de colores.


    public:
        PoolScene(State* state, Game* g, GameScene* reward);
        ~PoolScene();
        inline GameScene* getRewardScene() const {return _reward;}
    };

}
