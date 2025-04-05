#pragma once

#include <vector>

#include "Singleton.h"
#include "Inventory.h"

class InventoryManager : public Singleton<InventoryManager> {

	friend Singleton<InventoryManager> ;

    Inventory _inventory;

public:
	InventoryManager();

	virtual ~InventoryManager();

    void swapInventory(Inventory inv);

public:
    // Consultar
    std::vector<entity_t> getEffectBalls();
    entity_t getWhiteBall();
    entity_t getStick();
    Inventory::Perma& getPerma();

    // Añadir
    void addBall(entity_t ball);

    // Gestionar
    void swapBall(entity_t in, entity_t out); 
    //! Veo conveniente solo usar la sobrecarga basada en ínices, pero los dejo los dos de momento
    void swapBall(entity_t newBall, int indexOfOldBall);

    void swapStick(entity_t newStick);

private:
    // Eliminar
    void removeBall();
    void removeStick();
};