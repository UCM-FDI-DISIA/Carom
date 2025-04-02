#include "Button.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Texture.h"
#include "Component.h"
#include "PhysicsUtils.h"

#include "RenderSpritesheetComponent.h"

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
    // Aquí se está haciendo un compromiso, en vez de pasar el componente de textura que rige
    // las dimensiones del botón se va a buscar entre los potenciales componentes de renderizado
    // 
    // IMPORTANTE
    // Se va a priorizar siempre a RenderTextureComponent respecto a RenderSpritesheetComponent
    //
    // Soy muy consciente de que esto es muy muy poco escalable
    
    RenderComponent* a_targetRenderer;

    if (_myEntity->tryGetComponent<RenderTextureComponent>()) {
        a_targetRenderer = _myEntity->getComponent<RenderTextureComponent>();
    }
    else if (_myEntity->tryGetComponent<RenderSpritesheetComponent>()) {
        a_targetRenderer = _myEntity->getComponent<RenderSpritesheetComponent>();
    }

    _buttonArea->setRenderer(a_targetRenderer);
    _transform = _myEntity->getComponent<TransformComponent>();

    // Si comento esto se muere el programa al hacer hover
    setOnHover([this]() -> void {/*std::cout << "hover" << std::endl;*/});
    setOnClick([this]() -> void {/*std::cout << "click" << std::endl;*/});
    setOnExit([this]() -> void {/*std::cout << "exit" << std::endl;*/});
}

void Button::handleEvent() {
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

void Button::ButtonData::setRenderer(RenderComponent* targetRenderer) {
    _targetRenderer = targetRenderer;
}

Button::RadialButton::RadialButton(float factor): _factor(factor)
{

}

void Button::RadialButton::setRenderer(RenderComponent* targetRenderer)
{
    ButtonData::setRenderer(targetRenderer);

    _radius = std::max(_targetRenderer->getRenderRect().w, _targetRenderer->getRenderRect().h) * _factor;
}

Button::ButtonData*
Button::RadialButton::clone()
{
    return new RadialButton(_factor);
} 

bool Button::RadialButton::isMouseInButton(std::pair<Sint32, Sint32> mousePos)
{
    SDL_Rect a_textRect = _targetRenderer->getRenderRect();
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
    SDL_Rect rect = _targetRenderer->getRenderRect();
    return InputHandler::Instance()->isMouseInRect(mousePos, rect);
}