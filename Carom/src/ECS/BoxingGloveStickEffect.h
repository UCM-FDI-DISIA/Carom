#pragma once

#include "StickEffectComponent.h"
namespace ecs {
    class BoxingGloveStickEffect : public StickEffectComponent {
    private:
        float _factor;
    public:
        BoxingGloveStickEffect(entity_t entity, float frictionFactor);
        ~BoxingGloveStickEffect();
        void applyEffect(entity_t target) override;
    };
}