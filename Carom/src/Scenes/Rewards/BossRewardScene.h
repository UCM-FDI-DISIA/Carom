#pragma once

#include "RewardScene.h"
#include "PoolScene.h"
#include <vector>

class InventoryManager;

/// @brief Recompensa que le otorga al jugador todas las bolas del jefe
class BossRewardScene : public RewardScene 
{    
public:
    BossRewardScene(Game* game, Reward reward);
    virtual ~BossRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;

private:
    //Devuelve verdadero si la selección de bolas es válida, es decir, si al eliminar las
    //bolas del inventario y al seleccionar las bolas de la recompensa no se supera el límite
    //de bolas del inventario
    void checkIfValid();

    //Checkea si la bola seleccionada para eliminar ya estaba seleccionada
    bool checkIfBallIsSelected(int ballId);

    //Checkea si la bola seleccionada para añadir ya estaba seleccionada
    bool checkIfBallIsObtained(int ballId);

    //Método auxiliar para comprobar si un elemento está en un vector
    inline bool hasElement(std::vector<int>& vec, int elem) {
        return std::find(vec.begin(), vec.end(), elem) != vec.end();
    }

    //Vector que guarda la información de las bolas obtenidas de la escena de pool
    std::vector<PoolScene::BallInfo> _obtainedBallsInfo;

    //Vector que guarda los indices de las bolas seleccionadas para añadir al inventario
    std::vector<int> _selectedBalls;
    InventoryManager* _inventory;

    //Vector que guarda los indices en el inventario de las bolas que se van a eliminar
    std::vector<int> _ballsToRemove;

    // Mostrar las bolas obtenidas y sus efectos (Ojo! No son las bolas del inventario, sino las de recompensa de piso)
    void createObtainedBalls();
    std::vector<RewardInfoDisplayComponent*> _effectRewardBoxes;
    void createBallInfoText(); // crea la info de cada bola.
    void showBallEffect(int i); // muestra bola.
    void hideBallEffect(int i); // esconde bola.
    void scrollObtainedBallEffect(int i); //Cambia el efecto que se muestra
};