#pragma once

#include "Reward.h"

/// @brief Fusión: Escoges dos bolas, que se fusionarán en una sola con los Efectos de ambas
class FusionReward : public Reward {
public:
    FusionReward() : Reward("fusion", Type::INSTANT) {

    }

    void applyReward() override {
        // TODO
    }
    
};