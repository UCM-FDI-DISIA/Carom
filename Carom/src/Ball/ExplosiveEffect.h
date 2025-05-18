#pragma once

#include "BallEffect.h"
#include <box2d/box2d.h>


class RigidBodyComponent;

/// @brief Efecto añadido por el palo lanzagranadas. La bola que lo reciba enviará un impulso a otras bolas en un radio cuando pase un tiempo determinado
class ExplosiveEffect : public BallEffect {
    float _explosionDelay, _explosionStart, _radius, _force;
    bool _exploded;
    RigidBodyComponent* _myRigidbody;

    /// @brief Método auxiliar para buscar las otras bolas y empujarlas
    void createExplosion();
public:

    __CMPID_DECL__(cmp::EXPLOSIVE_EFFECT);
    cmpId_t getEffectId() override {return cmp::EXPLOSIVE_EFFECT;}

    /// @brief Constructor de la bola explosiva
    /// @param ent Entidad a la que pertenece
    /// @param timeForExplosion tiempo en milisegundos hasta que explota
    /// @param radius radio en metros de la explosión
    /// @param force fuerza de empuje máxima (la fuerza es relativa a la distacia con la bola explosiva)
    ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force);
    ~ExplosiveEffect();

    void init() override;
    void update() override;

    void onHit(entity_t ent) {}
    void onStrikeEnd() override {}
    void onBeingTargeted() override {}
};
