#pragma once

#include "BallEffect.h"


class RigidBodyComponent;

/// @brief Cambia el linear damping del objeto en un factor, es añadido por el palo de guante de boxeo
class FrictionMultiplierEffect : public BallEffect {
    float _frictionFactor;
    RigidBodyComponent* _rigidBody;        
public:
    __EFFID_DECL__(effect::FRICTION_MULTIPLIER_EFFECT);
    effectId_t getEffectId() override {return effect::FRICTION_MULTIPLIER_EFFECT; }

    /// @brief La constructora del efecto de bola con fricción reducida
    /// @param entity La entidad a la que pertenece
    /// @param friction El factor por el que multiplica el linear damping del rigidBody
    FrictionMultiplierEffect(BallHandler* hndlr, float friction);
    ~FrictionMultiplierEffect();

    void init() override;
    void onStrikeEnd() override;
};
