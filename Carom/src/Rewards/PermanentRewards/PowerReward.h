#pragma once

#include "Reward.h"

/// @brief Poder: Añade una tirada máxima
class PowerReward : public Reward {
public:
    PowerReward() : Reward("power", Type::PERMANENT) {

    }

    void applyReward() override {
        auto inv = InventoryManager::Instance();

        inv->setPower(inv->getPower() + 1);
    }
};