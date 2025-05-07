#pragma once

#include "Reward.h"

/// @brief Carisma: Incrementa el valor base de la puntuación (Por defecto es 0)
class CharismaReward : public Reward {
protected:
    int _value;

public:
    CharismaReward() : Reward("charisma", Type::PERMANENT) {
        auto rng = RNG_Manager::Instance();
        rng->randomRange(10,51);
    }

    void applyReward() override {
        auto inv = InventoryManager::Instance();

        inv->setCharisma(inv->getCharisma() + _value);
    }
};