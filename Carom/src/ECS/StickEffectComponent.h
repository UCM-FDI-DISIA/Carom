#pragma once

#include "Component.h"

 namespace ecs {
    class StickEffectComponent : public Component {
    public:
        StickEffectComponent(entity_t entity) : Component(entity) {}
        virtual ~StickEffectComponent();

        virtual void applyEffect(entity_t target) = 0;

        void update() override {}
        void handleEvent() override {}
        void render(Camera* camera) override {}
    };
 }