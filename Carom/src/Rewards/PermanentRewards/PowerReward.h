#pragma once

#include "Reward.h"

/// @brief Poder: Añade una tirada máxima
class PowerReward : public Reward {
protected:
    int _value;

public:
    PowerReward() : Reward("power", Type::PERMANENT) {
        auto rng = RNG_Manager::Instance();
        rng->randomRange(10,51);
    }

    void applyReward() override {
        auto inv = InventoryManager::Instance();

        inv->setPower(inv->getPower() + _value);
    }
};