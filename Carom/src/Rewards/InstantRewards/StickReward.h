#pragma once

#include "Reward.h"

/// @brief Te da a elegir uno entre dos palos (puedes no escoger ninguno)
/// @name Desván
class StickReward : public Reward {
protected:
    // pair<stick, stick> _sticks // prefabs de palos aleatorios entre los que elige el jugador

public:
    StickReward() : Reward(Type::INSTANT) {
        // TODO
        // Seleccion de palos recompensa aleatorios
        // _stick.first = rng.get(...)
        // _stick.second = rng.get(...)
    }

    void applyReward() override {
        // TODO selección de palo y añadirlo al inventario
    }
    
};