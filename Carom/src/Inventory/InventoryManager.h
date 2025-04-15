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
    // Consultar
    std::vector<entity_t> getEffectBalls(GameScene& scene, std::vector<b2Vec2> positions = std::vector<b2Vec2>());
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