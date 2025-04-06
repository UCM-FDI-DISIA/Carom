#pragma once

#include <vector>

#include "Singleton.h"
#include "Inventory.h"

class InventoryManager : public Singleton<InventoryManager> {

	friend Singleton<InventoryManager> ;

    Inventory _inventory;

private:
	InventoryManager();
	virtual ~InventoryManager();

    inline bool init() {
        _inventory = Inventory();
        return true;
    }
    
    public:
    // Consultar
    std::vector<entity_t> getEffectBalls();
    entity_t getWhiteBall();
    entity_t getStick();
    Inventory::Perma& getPerma();
    
    // Añadir
    void addWhiteBall(entity_t ball);
    void addBall(entity_t ball);
    void addStick(entity_t stick);
    
    // Gestionar
    void swapInventory(Inventory inv);
    void swapBall(entity_t in, entity_t out); 
    //! Veo conveniente solo usar la sobrecarga basada en índices, pero los dejo los dos de momento
    void swapBall(entity_t newBall, int indexOfOldBall);

    void swapStick(entity_t newStick);

private:
    // Eliminar
    void removeWhiteBall();
    void removeBall(entity_t ball);
    void removeBall(int index);
    void removeAllBalls();
    void removeStick();
};