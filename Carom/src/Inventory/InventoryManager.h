#pragma once

#include <vector>

#include "Singleton.h"
#include "Inventory.h"

class entity_t;

class InventoryManager : public Singleton<InventoryManager> {

	friend Singleton<InventoryManager> ;

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