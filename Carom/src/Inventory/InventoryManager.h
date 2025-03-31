#pragma once

#include <vector>

#include "Singleton.h"
#include "Inventory.h"

class entity_t;

class InventoryManager : public Singleton<InventoryManager> {

	friend Singleton<InventoryManager> ;

public:
    std::vector<entity_t> getBalls();
    entity_t getStick();
    Inventory::Perma getPerma();
};