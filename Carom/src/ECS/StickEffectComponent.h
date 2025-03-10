#pragma once

#include "Component.h"

 namespace ecs {
    class StickEffectComponent : public Component {
    public:
        StickEffectComponent();
        virtual ~StickEffectComponent();

        virtual void aplyEffect() = 0;

        void update() override;
        void handleEvent() override {}
        void render(Camera* camera) override {}
    };
 }