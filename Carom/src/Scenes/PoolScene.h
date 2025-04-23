#pragma once
#include "GameScene.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"

#include <memory>

class ScenesManager;
class RNG_Manager;


class PoolScene: public UIScene {
protected:
    static constexpr int HOLES = 6;
    enum BallTypes{
            ROUND,
            BOSS
        };

    RNG_Manager& _rngm; // random manager

    std::shared_ptr<GameScene> _reward; //La recompensa al completar la escena
    std::shared_ptr<GameScene> _scene;
    
    b2WorldId _myB2WorldId; //El mundo de box2D

    void generateRndBallsPos(); // para la generación aleatoria de la pos de las bolas.

    entity_t generateHole(int i); // para generar el agujero según indice.

public:
    PoolScene(Game* g);
    ~PoolScene();

    void initObjects() override;
    void initFunctionalities() override;
};

