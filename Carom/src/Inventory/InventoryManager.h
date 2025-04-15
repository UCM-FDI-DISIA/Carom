#pragma once

#include <vector>

#include "Singleton.h"
#include "Inventory.h"
class GameScene;
class InventoryManager : public Singleton<InventoryManager> {

	friend Singleton<InventoryManager> ;
private:
	InventoryManager();
	virtual ~InventoryManager();

    inline bool init() {
        return true;
    }
    
    void loadInventoryWithPath(std::string path);

    
    public:
    static const int MAX_BALLS = 6;
    const std::string pathToInventory = "../../resources/prefabs/inventoryData/inventory.json";
    // Recibe una COPIA de las bolas del inventario, es decir, las genera a partir del json
    //
    //@param positions
    //Debe ser un vector de tamaño MAX_BALLS, ya que sino todas las bolas tendran posicion 0,0
    std::vector<entity_t> getEffectBalls(GameScene& scene, std::vector<b2Vec2> positions);
    entity_t getStick(GameScene& scene);
    Inventory::Perma& getPerma();
    
    // Añadir
    void addBall(entity_t ball);
    void addStick(entity_t stick);
    
    // Gestionar
    void loadStartingInventory();
    void loadSavedInventory();
    //! Veo conveniente solo usar la sobrecarga basada en índices, pero los dejo los dos de momento
    void swapBall(entity_t newBall, int indexOfOldBall);

private:
    // Eliminar
    void removeBall(int index);
    void removeAllBalls();
    void removeStick();
};