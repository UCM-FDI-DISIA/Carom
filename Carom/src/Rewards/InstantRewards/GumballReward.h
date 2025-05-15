#pragma once

#include "Reward.h"

/// @brief Máquina de chicles: Recibe una bola aleatoria
class GumballReward : public Reward {
protected:
    // ball_t _ball // prefab de bola aleatoria que va a recibir el jugador

public:
    GumballReward() : Reward("gumball", Type::INSTANT) {
        // TODO
        // Seleccion de bola recompensa aleatoria
        // _ball = rng.get(...)
    }

    void applyReward(RewardScene* rs) override {
        // TODO añadir bola al inventario
    }
    
};