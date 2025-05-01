#pragma once
#include "GameScene.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"
#include "Reward.h"


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

    RNG_Manager* _rngm; // random manager

    std::shared_ptr<GameScene> _reward; //La recompensa al completar la escena
    std::shared_ptr<GameScene> _scene;
    
    b2WorldId _myB2WorldId; //El mundo de box2D

    std::vector<RandomItem<std::shared_ptr<Reward>>> _rewards; // Todas la posibles recompensas, sacadas del json
    std::vector<std::shared_ptr<Reward>> _floorRewards; // Recompensas de cada agujero del piso

    int _bossHole;

    void generateMatchHoles(); // para la generación aleatoria de los agujeros de partida.

    entity_t generateHole(int i); // para generar el agujero según indice.

    void loadRewards(); // Rellena el vector de posibles recompensas
    void generateFloorRewards(); // genera las recompensas del piso
    void createRewardInfo();
    void showReward(int i);
    void hideReward(int i);

public:
    PoolScene(Game* g);
    ~PoolScene();

    void initObjects() override;
    void initFunctionalities() override;
};

