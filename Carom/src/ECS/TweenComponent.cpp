#include "TweenComponent.h"
#include "Tween.h"
#include "TransformComponent.h"

namespace ecs{
    TweenComponent::TweenComponent(entity_t ent): LogicComponent(ent){
        _tweens = std::vector<Tween*>();
        _paused = false;
    }
    
    TweenComponent::~TweenComponent(){
        for(auto t : _tweens) delete t;
    }

    void TweenComponent::init(){
        _myTr = _myEntity->getComponent<TransformComponent>();
    }
    
    void TweenComponent::update(){
        if(!_paused){
            for(Tween* t: _tweens){
                t->update();
            }
        }
        
        //si se han acabado algunas, se matan
        
        _tweens.erase(std::remove_if(_tweens.begin(), _tweens.end(), [this](Tween* e){
            if(e->isAlive()) return false;
            else {
                delete e;
                return true;
            }
        }), _tweens.end());
        
    }
    
    void TweenComponent::pauseTweening() { _paused = true;}
    void TweenComponent::resumeTweening() { _paused = false;}
    
    void TweenComponent::easeValue(float* value, float finalValue, float duration, tween::tweenType type){
        uint32_t durationMS = duration * 1000;
        Tween* t;
        switch (type){
            case tween::LINEAR:
                t = new LinearTween(value, finalValue, durationMS);
            break;
            case tween::EASE_IN_EXPO:
    
            break;
            case tween::EASE_OUT_QUINT:
    
            break;
            case tween::EASE_IN_BACK:
                t = new EaseInBackTween(value, finalValue, durationMS);
            break;
        }
    
        _tweens.push_back(t);
    }
    
    void TweenComponent::easePosition(Vector2D finalPos, float duration, tween::tweenType type){
        easeValue(&_myTr->_position.x, finalPos.getX(), duration, type);
        easeValue(&_myTr->_position.y, finalPos.getY(), duration, type);
    }
    
    void TweenComponent::easeRotation(float finalRot, float duration, tween::tweenType type){
        easeValue(&_myTr->_rotation, finalRot, duration, type );
    }
}
