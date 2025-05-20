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
    
    b2WorldId _myB2WorldId; //El mundo de box2D
    static constexpr int POSITIONS = 6;
    
    std::vector<entity_t> _holes, _balls;
    
    
public: 
    inline std::vector<BallInfo> getBallsInfo() const {return _ballsInfo; }

    /// @brief Devuelve solo las bolas disponibles
    std::vector<BallInfo> getFreeBallsInfo() const {
        std::vector<BallInfo> v;
        for(auto b: _ballsInfo)
            if(b.free) v.push_back(b);
        return v;
    }


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
    // void showBallEffect(int i); // muestra bola.
    // void hideBallEffect(int i); // esconde bola.
    void scrollBallEffect(int i) override; //Cambia el efecto que se muestra

    /// @brief Genera efectos aleatorios para las 6 bolas
    void initRandomEffects();

    /// @brief Método auxiliar para intentar añadir un efecto a una bola
    /// @param index Nº de la bola 
    /// @param chance probabilidad de añadirle un efecto
    /// @param possibleEffects Efectos que pueden ser añadidos a la bola
    void addNewEffect(int index, float chance, std::vector<RandomItem<BallId>>& possibleEffects);
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

