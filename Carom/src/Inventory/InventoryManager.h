#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "Singleton.h"
#include "Inventory.h"
#include "ItemIDs.h"
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

    
    //actualiza el json a partir del mapa dado
    //@param data
    //mapa que se va a convertir en json
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

    // Recibe una COPIA del stick del inventario, es decir, lo genera a partir del json
    entity_t getStick(GameScene& scene);
    
    // Añade una entidad de bola al inventario. retorna true o false si se ha cosneguido meter la bola o no por el hueco
    bool addBall(entity_t ball);
    // Añade una entidad de bola al inventario. retorna true o false si se ha cosneguido meter la bola o no por el hueco
    bool addBall(std::vector<int> ids);
    //Anade el palo al inventario
    void addStick(entity_t stick);
    //Anade el palo al inventario
    void addStick(int id);

    //guardar todas las bolas en el inventario, sobreescribiendo las que ya habia
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

    // Elimina una bola del inventario
    //@param index
    //Slot de la bola que se quiere borrar
    void removeBall(int index);
    //Retorna todos los efectos de una bola
    //@param index
    //Slot de la bola que se quiere copiar los efectos
    std::vector<BallId> getEffectsFromBall(int index);
private:
    //Elimina todas las bolas del inventario
    void removeAllBalls();
    //Elimina el palo del inventario, dejando el inicial
    void removeStick();
};