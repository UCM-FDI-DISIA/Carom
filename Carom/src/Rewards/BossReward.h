#pragma once

#include "Reward.h"

class BossReward : public Reward {
public:
    BossReward() : Reward(Type::BOSS) {

    }

    void applyReward() override {
        // TODO: Obtención bolas mesa pool
    }
};