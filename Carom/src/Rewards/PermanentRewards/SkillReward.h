#pragma once

#include <utility>

#include "Reward.h"

using strength = int;
using skillType = int;
using skill = std::pair<skillType, strength>;

/// @brief "Soltura": Incrementa el valor de una jugada (Golpe, Combo o Carambola) a elegir entre dos
class SkillReward : public Reward {
protected:
    enum SkillType {
        HitEase,
        ComboEase,
        CaromEase
    };

    std::pair<skill, skill> _skills; // Skills entre las que puede elegir el jugador

public:
    SkillReward() : Reward("skill", Type::PERMANENT) {
        // TODO 
        // Selección de skill y valores aleatorios
        // skillType sk = rng.get(...)
        // strength st = rng.getRndRange(...)

        // _skills = std::make_pair(
        //     skill(sk , ...),
        //     skill(st , ...)
        // );
    }

    void applyReward() override {
        // TODO selección de skill y añadirlo al inventario
    }
};