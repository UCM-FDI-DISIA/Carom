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
    std::vector<entity_t> getBalls();
    Texture* getStickTexture();
    StickEffectComponent* getStickEffect();
    Inventory::Perma& getPerma();

    // Añadir
    void addBall(entity_t ball);

    // Gestionar
    void swapBall(entity_t in, entity_t out);
    void swapStick();

private:
    // Eliminar
    void removeBall();
    void removeStick();
};