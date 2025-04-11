#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"
// No sé si es mejor crearme mi propio enum Perma o usar el que ya existe en Inventory.h
// #include "Inventory.h"

class ScenesManager;
class RNG_Manager;


class PoolScene: public UIScene {
protected:
    static constexpr int HOLES = 6;
    enum BallTypes{
            ROUND,
            BOSS
        };

    enum Instant {
        DEFAULT, // Empty reward
        FUSION,
        GUMBALL_MACHINE,
        STORAGE_ROOM,
        CAULDRON
    };

    struct Perma {
        int hitEase = 0, comboEase = 0, caromEase = 0;
        int charisma = 0;   // carisma
        int power = 0;      // poder
        float cunning = 1.0f;  // picardía
    };

    struct Reward {
        Instant instantReward;
        Perma permanentReward;
    };

    RNG_Manager* _rngm; // random manager
    b2WorldId _myB2WorldId; //El mundo de box2D

    std::vector<RandomItem<Reward>> _rewards; // Todas la posibles recompensas, sacadas del json
    std::vector<Reward> _floorRewards; // Recompensas de cada agujero del piso

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
};

