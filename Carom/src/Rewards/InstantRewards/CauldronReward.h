#pragma once

#include "Reward.h"

/// @brief Añades a una bola de tu kit uno de dos efectos a elegir.
/// @name Caldero
class CauldronReward : public Reward {
protected:
    // pair<effect, effect> _effects // prefabs de efectos aleatorios entre los que elige el jugador

public:
    CauldronReward() : Reward(Type::INSTANT) {
        // TODO
        // Seleccion de efectos recompensa aleatorios
        // _effect.first = rng.get(...)
        // _effect.second = rng.get(...)
    }

    void applyReward() override {
        // TODO selección de efecto y apliarlo a la bola seleccionada
    }
    
};