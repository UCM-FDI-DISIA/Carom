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
class RewardInfoDisplayComponent;

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
    static constexpr int POSITIONS = 6;
    
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
        int scrollIndex = 0;
        bool free = true;
    };

    std::vector<BallInfo> _ballsInfo;
    const float _chanceForMultipleEffect = 0.25f;
    std::vector<RewardInfoDisplayComponent*> _effectRewardBoxes;

    std::vector<BallInfo> getBallsInfo() const {return _ballsInfo; }
    void saveBalls();

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
    void createBallInfoText(); // crea la info de cada bola.
    void showBallEffect(int i); // muestra bola.
    void hideBallEffect(int i); // esconde bola.
    void scrollBallEffect(int i); //Cambia el efecto que se muestra

    void initRandomEffects();
    void addNewEffect(int index, float chance, std::vector<RandomItem<EffectType>>& possibleEffects);
    std::string getTextureName(EffectType effect);
    std::string getEffectName(EffectType effect);

    // ----------

    // --- CALLBACKS ---
    void createCallbacks();
    // ----------

public:
    PoolScene(Game* g);
    ~PoolScene();

    void initObjects() override;
    void initFunctionalities() override;
};

