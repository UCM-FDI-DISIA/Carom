#pragma once

#include "Reward.h"

/// @brief Recibe una bola aleatoria
/// @name Máquina de chicles
class GumballReward : public Reward {
protected:
    // ball_t _ball // prefab de bola aleatoria que va a recibir el jugador

public:
    GumballReward() : Reward(Type::INSTANT) {
        // TODO
        // Seleccion de bola recompensa aleatoria
        // _ball = rng.get(...)
    }

    void applyReward() override {
        // TODO añadir bola al inventario
    }
    
};