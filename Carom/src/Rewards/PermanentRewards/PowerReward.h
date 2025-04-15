#pragma once

#include "Reward.h"

/// @brief Añade una tirada máxima
/// @name Poder
class PowerReward : public Reward {
protected:
    int _value;

public:
    PowerReward() : Reward(Type::PERMANENT) {
        // _value = rng.getRndRange(...)
    }

    void applyReward() override {
        // TODO aplicar poder al inventario
        // InventoryManager::Instance()->addPower();
    }
};