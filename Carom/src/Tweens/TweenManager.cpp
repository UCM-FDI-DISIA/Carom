#include "TweenManager.h"
#include "Tween.h"
#include "TransformComponent.h"

TweenManager::TweenManager(){
    _tweens = std::vector<Tween*>();
    _paused = false;
}

TweenManager::~TweenManager(){
    for(auto t : _tweens) delete t;
}

void TweenManager::update(){
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

void TweenManager::removeTween(Tween* t){
    t->setAlive(false);
}

void TweenManager::pauseTweening() { _paused = true;}
void TweenManager::resumeTweening() { _paused = false;}

void TweenManager::easeValue(float* value, float finalValue, float duration, tween::tweenType type){
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

void TweenManager::easePosition(ecs::TransformComponent* tr, Vector2D finalPos, float duration, tween::tweenType type){
    easeValue(&tr->_position.x, finalPos.getX(), duration, type);
    easeValue(&tr->_position.y, finalPos.getY(), duration, type);
}

void TweenManager::easeRotation(ecs::TransformComponent* tr, float finalRot, float duration, tween::tweenType type){

}