#include "FrameAnimatorComponent.h"

#include "RenderTextureComponent.h"
#include "Entity.h"
#include "SDLUtils.h"

namespace ecs{

    FrameAnimatorComponent::FrameAnimatorComponent(entity_t ent, Frame* startingFrame)
    : LogicComponent(ent),
    _startingFrame(startingFrame), 
    _currentFrame(startingFrame) {}

    void
    FrameAnimatorComponent::init() {
        _renderTextureComponent = _myEntity->getComponent<RenderTextureComponent>();
        _frameStartTimestamp = sdlutils().currTime();
        enableFrame();
    }

    void
    FrameAnimatorComponent::update() {
        if (sdlutils().currTime() - _frameStartTimestamp >= _currentFrame->_milliseconds)
        {
            _currentFrame->_exitCallback();
            if (_currentFrame->_nextFrame == nullptr) {
                applyExitCase();
            }
            _currentFrame = _currentFrame->_nextFrame;
            enableFrame();
        }
    }

    void
    FrameAnimatorComponent::applyExitCase() {
        switch (_exitCase) {
            case DISABLE:
                this->setEnabled(false);
                break;
            case KILL_MYSELF:
                _myEntity->setAlive(false);
                break;
            case LOOP:
                _currentFrame = _startingFrame;
                enableFrame();
            default:
                break;
        }
    }

    void
    FrameAnimatorComponent::enableFrame() {
        _frameStartTimestamp = sdlutils().currTime();
        _renderTextureComponent->setTexture(_currentFrame->_texture, _currentFrame->_scale);
        _currentFrame->_enterCallback();
    }
}