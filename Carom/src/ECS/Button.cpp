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

void Button::setEntity(entity_t other)
{
    _myEntity = other;

    RenderComponent* a_targetRenderer = _myEntity->getRenderer();

    _buttonArea->setRenderer(a_targetRenderer);
    _transform = _myEntity->getComponent<TransformComponent>();
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
    
    setEntity(_myEntity);

    // Si comento esto se muere el programa al hacer hover
    setOnHover([this]() -> void {/*std::cout << "hover" << std::endl;*/});
    setOnClick([this]() -> void {/*std::cout << "click" << std::endl;*/});
    setOnRightClick([this]() -> void {/*std::cout << "rightclick" << std::endl;*/});
    setOnExit([this]() -> void {/*std::cout << "exit" << std::endl;*/});
}

void Button::handleEvent() {
    InputHandler* input = &ih();

    if(_buttonArea->isMouseInButton(input->getMousePos())){
        if(!_isInside){
            _isInside = true;
            _onHover();
        }
        if(input->mouseButtonDownEvent()){
            if(input->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)){
                _onClick();
            }
            
            if(input->getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT)){
                _onRightClick();
            }
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
    return new TextureButton(_rotated);
}

bool Button::TextureButton::isMouseInButton(std::pair<Sint32, Sint32> mousePos)
{
    SDL_Rect rect = _targetRenderer->getRenderRect();
    if (_rotated)
    {
        rect.x += rect.w /2;
        rect.y += rect.h /2;

        int aux = rect.w;
        rect.w = rect.h;
        rect.h = aux;

        rect.x -= rect.w /2;
        rect.y -= rect.h /2;
    }
    return InputHandler::Instance()->isMouseInRect(mousePos, rect);
}
