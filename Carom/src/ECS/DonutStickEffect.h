#pragma once

#include "StickEffectComponent.h"
namespace ecs {
    class DonutStickEffect : public StickEffectComponent {
    private:
        float _factor;
    public:
        __CMPID_DECL__(cmp::DONUT_STICK);

        DonutStickEffect(entity_t entity) : StickEffectComponent(entity) {}
        ~DonutStickEffect() {}
        void applyEffect(entity_t target) override;
        void init() override {}
    };
}