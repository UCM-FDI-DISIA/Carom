#pragma once

#include "Reward.h"

/// @brief Recibes todas la bolas restantes de la mesa se pool y avanzas de piso
class BossReward : public Reward {
public:
    BossReward() : Reward("boss", Type::BOSS) {

    }

    void applyReward(RewardScene*) override {
        // TODO: Obtención bolas mesa pool
    }
};