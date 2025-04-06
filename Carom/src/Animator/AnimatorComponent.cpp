#include "AnimatorComponent.h"
#include <exception>
#include "Entity.h"
#include "SDLUtils.h"

AnimatorComponent::AnimatorComponent(entity_t ent,  Animation* anim):
LogicComponent(ent),
_animation(anim),
_frameIndex(0) {
    if (nullptr == anim) 
        throw std::invalid_argument("[AnimatorComponent::AnimatorComponent] No se acepta animación nula");
}

void
AnimatorComponent::init(){
    _myRenderer = _myEntity->getComponent<RenderSpritesheetComponent>();
    _frameStartTimestamp = sdlutils().currTime();
    _myRenderer->setFrame(_animation->_frameList[_frameIndex].frame);
}

void
AnimatorComponent::update() {
    if (sdlutils().currTime() - _frameStartTimestamp >= _animation->_frameList[_frameIndex].getActiveMiliseconds()) {
        
        // Actualiza el timestamp
        _frameStartTimestamp = sdlutils().currTime();
        
        // Si quedan frames en la animación entra al nuevo frame
        if (_animation->_frameList.size() -1 > _frameIndex) {
            _myRenderer->setFrame(_animation->_frameList[++_frameIndex].frame);
        }
        // Si no quedan ejecuta el fin de animación según tipo de animación
        else animationEnd(_animation->_animType);
    }
}

void
AnimatorComponent::animationEnd (Animation::AnimationType animType) {
    switch (animType) {
        case Animation::LOOP :
            restartAnimation();
            break;
        case Animation::KILLMYSELF :
            _myEntity->setAlive(false);
            break;
        case Animation::TURNOFF :
            this->setEnabled(false);
            break;
    }
}

void
AnimatorComponent::restartAnimation() {
    _frameIndex = 0;
    _myRenderer->setFrame(_animation->_frameList[_frameIndex].frame);
}