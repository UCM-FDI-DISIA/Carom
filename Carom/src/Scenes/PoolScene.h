#pragma once
#include "GameScene.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"
#include "UIScene.h"
#include "RewardScene.h"
#include "ItemIDs.h"

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

    // std::shared_ptr<GameScene> _reward; //La recompensa al completar la escena
    // std::shared_ptr<GameScene> _scene;
    
    b2WorldId _myB2WorldId; //El mundo de box2D
    static constexpr int POSITIONS = 6;
    
    std::vector<entity_t> _holes, _balls;
    
    
    //BallInfo púbico para acceder a la información de las bolas de la PoolScene como Itadori.
    public: 
        struct BallInfo{
            std::vector<BallId> effects;
            int scrollIndex = 0;
            bool free = true;

            bool operator==(const BallInfo& other) const {
                return effects == other.effects;
            }

             bool operator!=(const BallInfo& other) const {
                return !(effects == other.effects);
            }
        };

        std::vector<BallInfo> _ballsInfo;
        std::vector<BallInfo> getBallsInfo() const {return _ballsInfo; }

    protected:
    const float _chanceForMultipleEffect = 0.25f;
    std::vector<RewardInfoDisplayComponent*> _effectRewardBoxes;

    void createCurrentFloorUI();

    // --- AGUJEROS Y RECOMPENSAS ---
    std::vector<RewardScene::Reward> _floorRewards; // Recompensas de cada agujero del piso

    int _bossHole;

    void generateMatchHoles(); // para la generación aleatoria de los agujeros de partida.

    entity_t generateHole(int i); // para generar el agujero según indice.

    void chooseRewards(std::vector<RewardScene::Reward>& possibleRewards, int amount); // Rellena el vector de posibles recompensas
    void generateFloorRewards(); // genera las recompensas del piso
    std::shared_ptr<RewardScene> createRewardScene(RewardScene::Reward r);
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
    void addNewEffect(int index, float chance, std::vector<RandomItem<BallId>>& possibleEffects);
    std::string getTextureName(BallId effect);
    std::string getEffectName(BallId effect);

    // ----------

    // --- CALLBACKS ---
    void createCallbacks();
    // ----------

    void setBossBallTexture();

public:
    PoolScene(Game* g);
    ~PoolScene();

    void initObjects() override;
};

