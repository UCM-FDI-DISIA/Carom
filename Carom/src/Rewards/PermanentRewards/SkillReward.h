#pragma once

#include <utility>

#include "Reward.h"
#include "InventoryManager.h"

using strength = int;
using skillType = int;
using skill = std::pair<skillType, strength>;

/// @brief "Soltura": Incrementa el valor de una jugada (Golpe, Combo o Carambola) a elegir entre dos
class SkillReward : public Reward {
public:
    enum SkillType {
        HitEase,
        ComboEase,
        CaromEase
    };

protected:
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

        // temporal
        _skills = std::make_pair(
                skill(HitEase, 5), 
                skill(ComboEase, 5)
            );
    }

    inline skill getSkill1() const { return _skills.first;};
    inline skill getSkill2() const { return _skills.second;};

    void applyReward() override {}

    /// @brief Guarda en el inventario la recompensa seleccionada. Llamar a esta función desde el callback del botón de la UI
    void applyReward(skill s) {
        auto inv = InventoryManager::Instance();
        switch(s.first) {
            case SkillType::HitEase:
                inv->setHitEase(inv->getHitEase() + s.second);
                break;
            case SkillType::ComboEase:
                inv->setComboEase(inv->getComboEase() + s.second);
                break;
            case SkillType::CaromEase:
                inv->setCaromEase(inv->getCaromEase() + s.second);
                break;
        }
    }
};