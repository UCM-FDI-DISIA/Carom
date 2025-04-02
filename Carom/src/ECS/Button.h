#pragma once
#include "HandleEventComponent.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include <functional>
#include "SDL.h"
#include "RenderComponent.h"

class Button : public HandleEventComponent
{
public:

    void setEnabled(bool state) override;

    class ButtonData
    {
    public:

        ButtonData() {}

        virtual ButtonData* clone() = 0;

        virtual bool isMouseInButton(std::pair<Sint32, Sint32> mousePos) = 0;

        /// @brief Pensado para ser llamado dentro del init de Button
        /// @param _targetRenderer Componente de textura que recibe el click
        virtual void setRenderer(RenderComponent* targetRenderer);
        
    protected:
        RenderComponent* _targetRenderer = nullptr;
    };

    /// @brief Define un area toroidal a partir de la dimension mayor del objeto renderizable
    class RadialButton: public ButtonData
    {
    public:
        RadialButton(float factor = 1.0f);

        ButtonData* clone();
        void setRenderer(RenderComponent* targetRenderer) override;
        bool isMouseInButton(std::pair<Sint32, Sint32> mousePos) override;
    private:
        float _radius;
        float _factor;
    };

    class TextureButton: public ButtonData
    {
    public:
        TextureButton() {};
        ButtonData* clone();
        bool isMouseInButton(std::pair<Sint32, Sint32> mousePos) override;
    };


private:
    ButtonData* _buttonArea;
    TransformComponent* _transform;
    std::function<void()> _onHover;
    std::function<void()> _onClick;
    std::function<void()> _onExit;
    std::function<void()> _onDisable;

    bool _isInside;

public:
    Button(Entity* ent);
    Button(Entity* ent, ButtonData& buttonType);
    virtual ~Button();

    void handleEvent() override;
    void init() override;

    void setOnHover(std::function<void()> f) {_onHover = f;};
    void setOnClick(std::function<void()> f) {_onClick = f;};
    void setOnExit(std::function<void()> f) {_onExit = f;};
    void setOnDisable(std::function<void()> f) {_onDisable = f;};

    __CMPID_DECL__(cmp::BUTTON);
};