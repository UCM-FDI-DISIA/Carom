#include "Button.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Texture.h"

#include "PhysicsUtils.h"

namespace ecs
{
    Button::Button(Entity* ent) : HandleEventComponent(ent), _onHover(), _onClick(), _onExit(), _isInside() 
    {
        _buttonArea = new TextureButton();
    }

    Button::Button(Entity* ent, ButtonData* buttonType) : HandleEventComponent(ent), _buttonArea(_buttonArea), _onHover(), _onClick(), _onExit(), _isInside()
    {}
    
    void Button::init()
    {
        _buttonArea->setTextureComponent(_myEntity->getComponent<RenderTextureComponent>());
        _transform = _myEntity->getComponent<TransformComponent>();

        setOnHover([this]() -> void {std::cout << "hover" << std::endl;});
        setOnClick([this]() -> void {std::cout << "click" << std::endl;});
        setOnExit([this]() -> void {std::cout << "exit" << std::endl;});
    }

    void Button::handleEvent()
    {
        InputHandler* input = InputHandler::Instance();

        if(_buttonArea->isMouseInButton(input->getMousePos())){
            if(!_isInside){
                _isInside = true;
                _onHover();
            }
            if(input->mouseButtonDownEvent() && input->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)){
                _onClick();
            }
        }
        else if(_isInside){
            _isInside = false;
            _onExit();
        }
    }

    void Button::ButtonData::setTextureComponent(RenderTextureComponent* targetRenderer)
    {
        _targetRenderer = targetRenderer;
    }

    void Button::ExternalTorusButton::setTextureComponent(RenderTextureComponent* targetRenderer)
    {
        ButtonData::setTextureComponent(targetRenderer);

        _internalRadius = std::max(_targetRenderer->getRect().w, _targetRenderer->getRect().h);

        _externalRadius = _internalRadius + (_internalRadius*_externalRadiusFactor);
    }

    bool Button::ExternalTorusButton::isMouseInButton(std::pair<Sint32, Sint32> mousePos)
    {
        SDL_Rect a_textRect = _targetRenderer->getRect();
        std::pair<Sint32, Sint32> a_buttonCenter = {a_textRect.x+ a_textRect.w/2, a_textRect.y+ a_textRect.h/2};
        Vector2D a_mouseToButtonVec = 
        {
            (float)mousePos.first - (float)a_buttonCenter.first, 
            (float)mousePos.second - (float)a_buttonCenter.second
        };
        float a_vecDistance = a_mouseToButtonVec.magnitude();

        if (a_vecDistance > _internalRadius && a_vecDistance < _internalRadius)
            return true;
        else
            return false;
    }

    bool Button::TextureButton::isMouseInButton(std::pair<Sint32, Sint32> mousePos)
    {
        SDL_Rect rect = _targetRenderer->getRect();
        return InputHandler::Instance()->isMouseInRect(mousePos, rect);
    }
}