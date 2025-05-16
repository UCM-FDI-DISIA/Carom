#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "Singleton.h"
#include "Inventory.h"
#include "PoolScene.h"
class GameScene;
using json = nlohmann::json;


class InventoryManager : public Singleton<InventoryManager> {

	friend Singleton<InventoryManager> ;
private:
	InventoryManager();
	virtual ~InventoryManager();

    inline bool init() {
        return true;
    }
    
    //carga el inventario con el path
    void loadInventoryWithPath(std::string path);

    void updateData(json data);
    int getParameterValue(std::string key);
    void setParameterValue(std::string key, int value);

    
    public:
    static const int MAX_BALLS = 6;
    const std::string pathToInventory = "../../resources/prefabs/inventoryData/inventory.json";
    // Recibe una COPIA de las bolas del inventario, es decir, las genera a partir del json
    //
    //@param positions
    //Debe ser un vector de tamaño MAX_BALLS, ya que sino todas las bolas tendran posicion 0,0
    std::vector<entity_t> getEffectBalls(GameScene& scene, std::vector<b2Vec2> positions);
    entity_t getStick(GameScene& scene);
    
    // Añadir. retorna true o false si se ha cosneguido meter la bola o no
    bool addBall(entity_t ball);
    void addStick(entity_t stick);

    void saveBalls(std::vector<entity_t> balls);

    int getNumberOfEffectBalls();
    
    // Gestionar
    //inventario predefinido, con el kit basico de una nueva partida
    void loadStartingInventory();

    //inventario guardado de una partida anterior
    void loadSavedInventory();

    //inventario guardado de una partida anterior
    void loadInventoryNamed(std::string nameOfInventory);
    
    //copia inventory.json a savedInventory.json, para asi guardar la partida
    void exportInventoryToSave();

    //! Veo conveniente solo usar la sobrecarga basada en índices, pero los dejo los dos de momento
    void swapBall(entity_t newBall, int indexOfOldBall);

    //Perma
    int getHitEase();
    void setHitEase(int i);

    int getComboEase();
    void setComboEase(int i);

    int getCaromEase();
    void setCaromEase(int i);

    int getCharisma();
    void setCharisma(int i);

    int getPower();
    void setPower(int i);

    float getCunning();
    void setCunning(float f);

    // Eliminar
    void removeBall(int index);
    std::vector<PoolScene::EffectType> getEffectsFromBall(int index);
private:
    void removeAllBalls();
    void removeStick();
};