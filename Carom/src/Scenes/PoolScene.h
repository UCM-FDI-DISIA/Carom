#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"

class ScenesManager;
class RNG_Manager;


class PoolScene: public UIScene {
protected:
    static constexpr int HOLES = 6;
    enum BallTypes{
            ROUND,
            BOSS
        };

    RNG_Manager* _rngm; // random manager
    GameScene* _reward; //La recompensa al completar la escena
    b2WorldId _myB2WorldId; //El mundo de box2D

    void generateRndBallsPos(); // para la generación aleatoria de la pos de las bolas.
    void generateTable(); // para generar la mesa.
    entity_t generateHole(int i); // para generar el agujero según indice.
    void generateTableBackground(); // para generar el fondo de la mesa.

public:
    PoolScene(Game* g);
    ~PoolScene();
};

