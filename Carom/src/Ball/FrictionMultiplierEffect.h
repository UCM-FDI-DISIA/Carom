#pragma once

#include "BallEffect.h"

namespace ecs {
    class RigidBodyComponent;

    /// @brief Cambia el linear damping del objeto en un factor
    class FrictionMultiplierEffect : public BallEffect {
        float _frictionFactor;
        RigidBodyComponent* _rigidBody;        
    public:
        __CMPID_DECL__(cmp::FRICTION_MULTIPLIER);

        FrictionMultiplierEffect(entity_t entity, float friction);
        ~FrictionMultiplierEffect();

        void init() override;
        void onStrikeEnd() override;
    };
}