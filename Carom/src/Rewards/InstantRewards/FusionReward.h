#pragma once

#include "Reward.h"

/// @brief Escoges dos bolas, que se fusionarán en una sola con los Efectos de ambas
/// @name Fusión
class FusionReward : public Reward {
public:
    FusionReward() : Reward(Type::INSTANT) {

    }

    void applyReward() override {
        // TODO
    }
    
};