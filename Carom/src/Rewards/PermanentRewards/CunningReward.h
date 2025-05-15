#pragma once

#include "Reward.h"

/// @brief Picardía: Reduce en un porcentaje los puntos a alcanzar en todas las rondas futuras
class CunningReward : public Reward {
protected:
    float _value; // (0,1). El porcentaje de puntos que se descuenta

public:
    CunningReward() : Reward("cunning", Type::PERMANENT) {
        auto rng = RNG_Manager::Instance();
        _value = rng->randomRange(0.01f,0.05f);
    }

    void applyReward(RewardScene* rs) override {
        auto inv = InventoryManager::Instance();

        inv->setCunning(inv->getCunning() - _value);
    }
};