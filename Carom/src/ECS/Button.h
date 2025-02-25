#pragma once
#include "HandleEventComponent.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include <functional>

namespace ecs {
    class Button : public ecs::Component
    {
    private:
        RenderTextureComponent* _targetRenderer;
        TransformComponent* _transform;
        std::function<void()> _onHover;
        std::function<void()> _onClick;
        std::function<void()> _onExit;

        bool _isInside;

    public:
        Button(Entity* ent);
        virtual ~Button(){}

        void handleEvent() override;
        void init() override;

        void setOnHover(std::function<void()> f) {_onHover = f;};
        void setOnClick(std::function<void()> f) {_onClick = f;};
        void setOnExit(std::function<void()> f) {_onExit = f;};

        __CMPID_DECL__(cmp::BUTTON);
    };
}