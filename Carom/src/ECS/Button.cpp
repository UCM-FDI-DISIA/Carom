#include "Button.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Texture.h"

namespace ecs
{
    Button::Button(Entity* ent) : Component(ent), _onHover(), _onClick(), _onExit(), _isInside() {}
    
    void Button::init()
    {
        _targetRenderer = _myEntity->getComponent<RenderTextureComponent>();
        _transform = _myEntity->getComponent<TransformComponent>();

        setOnHover([this]() -> void {std::cout << "hover" << std::endl;});
        setOnClick([this]() -> void {std::cout << "click" << std::endl;});
        setOnExit([this]() -> void {std::cout << "exit" << std::endl;});
    }

    void Button::handleEvent()
    {
        InputHandler* input = InputHandler::Instance();
        SDL_Rect rect = _targetRenderer->getRect();

        if(input->isMouseInRect(input->getMousePos(), rect)){
            _isInside = true;
            _onHover();

            if(input->mouseButtonDownEvent()){
                _onClick();
            }
        }
        else if(_isInside){
            _isInside = false;
            _onExit();
        }
    }
}