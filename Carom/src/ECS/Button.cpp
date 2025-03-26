#include "Button.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Texture.h"

#include "PhysicsUtils.h"

    void Button::setEnabled(bool state)
    {
        _isEnable = state;
        if (!state) {
            //_onDisable();
        }
    }

    Button::Button(Entity* ent) : HandleEventComponent(ent), _onHover(), _onClick(), _onExit(), _isInside()
    {
        _buttonArea = new Button::TextureButton();
    }

    Button::Button(Entity* ent, ButtonData& buttonType) : HandleEventComponent(ent), _onHover(), _onClick(), _onExit(), _isInside()
    {
        _buttonArea = buttonType.clone();
    }

    Button::~Button() { delete _buttonArea; }
    
    void Button::init()
    {
        _buttonArea->setTextureComponent(_myEntity->getComponent<RenderTextureComponent>());
        _transform = _myEntity->getComponent<TransformComponent>();

        // Si comento esto se muere el programa al hacer hover
        setOnHover([this]() -> void {/*std::cout << "hover" << std::endl;*/});
        setOnClick([this]() -> void {/*std::cout << "click" << std::endl;*/});
        setOnExit([this]() -> void {/*std::cout << "exit" << std::endl;*/});
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
                std::cout << "LLAMAMOS\n";
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

    Button::RadialButton::RadialButton(float factor): _factor(factor){}

    void Button::RadialButton::setTextureComponent(RenderTextureComponent* targetRenderer)
    {
        ButtonData::setTextureComponent(targetRenderer);

        _radius = std::max(_targetRenderer->getRect().w, _targetRenderer->getRect().h) * _factor;
    }

    Button::ButtonData*
    Button::RadialButton::clone()
    {
        return new RadialButton(_factor);
    } 

    bool Button::RadialButton::isMouseInButton(std::pair<Sint32, Sint32> mousePos)
    {
        SDL_Rect a_textRect = _targetRenderer->getRect();
        std::pair<Sint32, Sint32> a_buttonCenter = {a_textRect.x+ a_textRect.w/2, a_textRect.y+ a_textRect.h/2};
        Vector2D a_mouseToButtonVec = 
        {
            (float)mousePos.first - (float)a_buttonCenter.first, 
            (float)mousePos.second - (float)a_buttonCenter.second
        };
        float a_vecDistance = a_mouseToButtonVec.magnitude();

        if (a_vecDistance < _radius)
            return true;
        else
            return false;
    }

    Button::ButtonData*
    Button::TextureButton::clone()
    {
        return new TextureButton();
    } 

    bool Button::TextureButton::isMouseInButton(std::pair<Sint32, Sint32> mousePos)
    {
        SDL_Rect rect = _targetRenderer->getRect();
        return InputHandler::Instance()->isMouseInRect(mousePos, rect);
    }