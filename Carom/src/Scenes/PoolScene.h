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
    
    RNG_Manager* _rngm; // random manager

    std::vector<entity_t> _holes, _balls;
    
    enum EffectType {
        ABBACUS,
        BOWLING,
        CRISTAL,
        PETANQUE,
        POKEBALL,
        QUANTIC,
        X2,
        NUM_EFFECTS
    };

    struct BallInfo{
        std::vector<EffectType> effects;
        bool free = true;
    };

    std::vector<BallInfo> _ballsInfo;
    const float _chanceForMultipleEffect = 0.1f;


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
    /*
    0- AbacusEffect
    1- BowlingEffect
    2- CristalEffect
    3- PetanqueEffect
    4- PokeballEffect
    5- QuanticEffect
    6- X2Effect
    Nota: el resto de efectos de bolas se ponen con palos, entonces no contarian para la Pool
    */

    std::string randomBallEffect(); // da un efecto de bola aleatorio.
    void generateBalls(); // genera las bolas.
    void createBallInfo(); // crea la info de cada bola.
    void showBallEffect(int i); // muestra bola.
    void hideBallEffect(int i); // esconde bola.

    void initBallsInfo();
    void addNewEffect(int index, float chance, std::vector<RandomItem<EffectType>>& possibleEffects);
    std::string getTextureName(EffectType effect);

    // ----------

    // --- CALLBACKS ---
    void createCallbacks();
    // ----------

public:
    PoolScene(Game* g);
    ~PoolScene();
};

