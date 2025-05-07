#pragma once

#include <utility>

#include "Reward.h"
#include "InventoryManager.h"

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

        // temporal
        _skills = std::make_pair(
                skill(HitEase, 5), 
                skill(ComboEase, 5)
            );
    }

    void applyReward() override {
        // Creación de botones
        // g->createButton(sdlutils().svgs().at("...").at("...").x, sdlutils().svgs().at("...").at("...").y, "Completo")
        // Selección de recompensa
        // skill selected;

        // TODO selección de skill y añadirlo al inventario

    }

    void rewardToInventory(skill s) {
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