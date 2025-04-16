#pragma once

#include "Reward.h"

/// @brief Poder: Añade una tirada máxima
class PowerReward : public Reward {
protected:
    int _value;

public:
    PowerReward() : Reward("power", Type::PERMANENT) {
        // _value = rng.getRndRange(...)
    }

    void applyReward() override {
        // TODO aplicar poder al inventario
        // InventoryManager::Instance()->addPower();
    }
};