#pragma once

#include "Reward.h"

/// @brief Caldero: Añades a una bola de tu kit uno de dos efectos a elegir.
class CauldronReward : public Reward {
protected:
    // pair<effect, effect> _effects // prefabs de efectos aleatorios entre los que elige el jugador

public:
    CauldronReward() : Reward("cauldron", Type::INSTANT) {
        // TODO
        // Seleccion de efectos recompensa aleatorios
        // _effect.first = rng.get(...)
        // _effect.second = rng.get(...)
    }

    void applyReward() override {
        // TODO selección de efecto y aplicarlo a la bola seleccionada
    }
    
};