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

/// @brief La escena donde vive el lobby del juego a.k.a el segundo crimen de guerra más grande de Carom
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
    
    
    public: 
    /// @brief Struct con la informacion de las bolas de cara a su uso como recompensa y su render 
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

    /// @brief El color del suelo cambia en funcion del piso
    void createCurrentFloorUI();

    // --- AGUJEROS Y RECOMPENSAS ---
    std::vector<RewardScene::Reward> _floorRewards; // Recompensas de cada agujero del piso

    int _bossHole;
    
    // para la generación aleatoria de los agujeros de partida.
    void generateMatchHoles(); 

    // para generar el agujero según indice.
    entity_t generateHole(int i); 

    // Rellena el vector de posibles recompensas
    void chooseRewards(std::vector<RewardScene::Reward>& possibleRewards, int amount); 

    // genera las recompensas del piso
    void generateFloorRewards(); 
    std::shared_ptr<RewardScene> createRewardScene(RewardScene::Reward r);

    /// @brief Genera las textBoxes de los hoyos
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

    /// @brief Genera efectos aleatorios para las 6 bolas
    void initRandomEffects();

    /// @brief Método auxiliar para intentar añadir un efecto a una bola
    /// @param index Nº de la bola 
    /// @param chance probabilidad de añadirle un efecto
    /// @param possibleEffects Efectos que pueden ser añadidos a la bola
    void addNewEffect(int index, float chance, std::vector<RandomItem<BallId>>& possibleEffects);
    std::string getTextureName(BallId effect);
    std::string getEffectName(BallId effect);

    // ----------

    // --- CALLBACKS ---
    /// @brief le añade callbacks a todos los botones 
    void createCallbacks();
    // ----------

    /// @brief Setea la bola de boss a bola de boss
    void setBossBallTexture();

public:
    PoolScene(Game* g);
    ~PoolScene();

    void initObjects() override;
};

