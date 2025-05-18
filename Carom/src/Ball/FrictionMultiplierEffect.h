#pragma once

#include "BallEffect.h"


class RigidBodyComponent;

/// @brief Cambia el linear damping del objeto en un factor, es añadido por el palo de guante de boxeo
class FrictionMultiplierEffect : public BallEffect {
    float _frictionFactor;
    RigidBodyComponent* _rigidBody;        
public:
    __CMPID_DECL__(cmp::FRICTION_MULTIPLIER);
    cmpId_t getEffectId() override {return cmp::FRICTION_MULTIPLIER; }

    /// @brief La constructora del efecto de bola con fricción reducida
    /// @param entity La entidad a la que pertenece
    /// @param friction El factor por el que multiplica el linear damping del rigidBody
    FrictionMultiplierEffect(entity_t entity, float friction);
    ~FrictionMultiplierEffect();

    void init() override;
    void onStrikeEnd() override;
};
