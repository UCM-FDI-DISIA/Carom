#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"
#include "Reward.h"


class ScenesManager;
class RNG_Manager;


class PoolScene: public UIScene {
protected:
    static constexpr int POSITIONS = 6;
    enum BallTypes{
            ROUND,
            BOSS
        };


    RNG_Manager* _rngm; // random manager
    b2WorldId _myB2WorldId; //El mundo de box2D


    // --- AGUJEROS Y RECOMPENSAS ---
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
    // ----------
    
    // --- EFECTOS DE BOLAS ---
    std::string randomBallEffect(); // da un efecto de bola aleatorio.
    void generateBalls(); // genera las bolas.
    void createBallInfo(); // crea la info de cada bola.
    void showBallEffect(int i); // muestra bola.
    void hideBallEffect(int i); // esconde bola.
    // ----------

public:
    PoolScene(Game* g);
    ~PoolScene();
};

