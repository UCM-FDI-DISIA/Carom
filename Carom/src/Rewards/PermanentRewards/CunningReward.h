#pragma once

#include "Reward.h"

/// @brief Picardía: Incrementa el valor base de la puntuación (Por defecto es 0)
class CunningReward : public Reward {
protected:
    float _value; // (0,1). No es el porcentaje de puntos que se descuenta, sino el porcentaje de puntos que quedan

public:
    CunningReward() : Reward("cunning", Type::PERMANENT) {
        // TODO generar valor aleatorio
        // _value = rng.getRndRange(...)
    }

    void applyReward() override {
        // TODO aplicar picardía al inventario
        // InventoryManager::Instance()->addCunning(_value);
    }
};