#pragma once

#include "Reward.h"

/// @brief Desván: Te da a elegir uno entre dos palos (puedes no escoger ninguno)
class StickReward : public Reward {
protected:
    // pair<stick, stick> _sticks // prefabs de palos aleatorios entre los que elige el jugador

public:
    StickReward() : Reward("stick", Type::INSTANT) {
        // TODO
        // Seleccion de palos recompensa aleatorios
        // _stick.first = rng.get(...)
        // _stick.second = rng.get(...)
    }

    void applyReward(RewardScene* rs) override {
        // TODO selección de palo y añadirlo al inventario
    }
    
};