#pragma once

#include "Reward.h"

/// @brief Carisma: Incrementa el valor base de la puntuación (Por defecto es 0)
class CharismaReward : public Reward {
protected:
    int _value;

public:
    CharismaReward() : Reward("charisma", Type::PERMANENT) {
        // TODO generar valor aleatorio
        // _value = rng.getRndRange(...)
    }

    void applyReward() override {
        // TODO aplicar carisma al inventario
        // InventoryManager::Instance()->addCharisma(_value);
    }
};