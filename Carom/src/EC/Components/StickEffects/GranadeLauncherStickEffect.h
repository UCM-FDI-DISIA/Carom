#pragma once 

#include "StickEffectComponent.h"

class Inventory;

/// @brief El palo lanzagranadas, que aplica explosiveEffect sobre una bola
class GranadeLauncherStickEffect : public StickEffectComponent {
    const float EXPLOSION_FORCE = 1, EXPLOSION_DELAY = 3000, EXPLOSION_RADIUS = 0.75f;
    friend Inventory;
public:
    __CMPID_DECL__(cmp::GRANADE_LAUCHER_STICK);

    /// @brief La constructora del palo terrorista
    /// @param ent La entidad a la que pertenece
    /// @param radius El radio de la explosión
    /// @param explosionForce La fuerza máxima de la explosión (depende de la distancia)
    /// @param explosionDelay El tiempo en milisegundos que tarda la bola en explotar
    GranadeLauncherStickEffect(entity_t ent);
    ~GranadeLauncherStickEffect();

    void applyEffect(entity_t ball) override;
};
