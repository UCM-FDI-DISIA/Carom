#pragma once
#include "HandleEventComponent.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include <functional>
#include "SDL.h"

namespace ecs {
    class Button : public ecs::HandleEventComponent
    {
    public:

        struct ButtonData
        {
            virtual bool isMouseInButton(std::pair<Sint32, Sint32> mousePos) = 0;

            /// @brief Pensado para ser llamado dentro del init de Button
            /// @param _targetRenderer Componente de textura que recibe el click
            virtual void setTextureComponent(RenderTextureComponent* targetRenderer);
            
        protected:
            RenderTextureComponent* _targetRenderer = nullptr;
        };

        /// @brief Define un area toroidal a partir de la dimension mayor del objeto renderizable
        struct ExternalTorusButton: public ButtonData
        {
            double _externalRadiusFactor = 1.0;

            void setTextureComponent(RenderTextureComponent* targetRenderer) override;
            bool isMouseInButton(std::pair<Sint32, Sint32> mousePos) override;
        private:
            float _internalRadius;
            float _externalRadius;
        };

        struct TextureButton: public ButtonData
        {
            bool isMouseInButton(std::pair<Sint32, Sint32> mousePos) override;
        };


    private:
        ButtonData* _buttonArea;
        TransformComponent* _transform;
        std::function<void()> _onHover;
        std::function<void()> _onClick;
        std::function<void()> _onExit;

        bool _isInside;

    public:
        Button(Entity* ent);
        Button(Entity* ent, ButtonData* buttonType);
        virtual ~Button(){}

        void handleEvent() override;
        void init() override;

        void setOnHover(std::function<void()> f) {_onHover = f;};
        void setOnClick(std::function<void()> f) {_onClick = f;};
        void setOnExit(std::function<void()> f) {_onExit = f;};

        __CMPID_DECL__(cmp::BUTTON);
    };
}