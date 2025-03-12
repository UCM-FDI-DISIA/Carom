#pragma once

#include "BallEffect.h"

namespace ecs {
    /// @brief Cambia el linear damping del objeto en un factor
    class FrictionMultiplierEffect : public BallEffect {
        float _frictionFactor;

    public:
        FrictionMultiplierEffect(entity_t entity, float friction);
        ~FrictionMultiplierEffect();

        void init() override;
        void onStrikeEnd() override;
    };
}