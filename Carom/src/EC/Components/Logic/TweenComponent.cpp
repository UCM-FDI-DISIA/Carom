#include "TweenComponent.h"
#include "Tween.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"


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
        int size = _tweens.size();
        for(int i =0; i < size; i++){
            _tweens[i]->update();
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

void TweenComponent::easeValue(float* value, float finalValue, float duration, tween::tweenType type, bool loop, Callback callback, Callback onUpdate){
    uint32_t durationMS = duration * 1000;

    Tween* t;
    switch (type){
        case tween::LINEAR:
            t = new LinearTween(value, finalValue, durationMS, loop, callback, onUpdate);
        break;
        case tween::EASE_IN_EXPO:
            t = new EaseInExponentialTween(value, finalValue, durationMS,loop, callback, onUpdate);
        break;
        case tween::EASE_OUT_QUINT:
            t = new EaseOutQuintTween(value, finalValue, durationMS, loop, callback, onUpdate);
        break;
        case tween::EASE_IN_BACK:
            t = new EaseInBackTween(value, finalValue, durationMS,loop, callback, onUpdate);
        break;
        case tween::EASE_IN_OUT_CUBIC:
            t = new EaseInOutCubicTween(value, finalValue, durationMS, loop, callback, onUpdate);
        break;
        case tween::EASE_OUT_ELASTIC:
            t = new EaseOutElasticTween(value, finalValue, durationMS, loop, callback, onUpdate);
        break;
    }

    _tweens.push_back(t);
}

void TweenComponent::easePosition(b2Vec2 finalPos, float duration, tween::tweenType type, bool loop, Callback callback, Callback onUpdate){
    easeValue(&_myTr->_position.y, finalPos.y, duration, type, loop);
    easeValue(&_myTr->_position.x, finalPos.x, duration, type, loop, callback, onUpdate);
}

void TweenComponent::easeRotation(float finalRot, float duration, tween::tweenType type,bool loop, Callback callback){
    easeValue(&_myTr->_rotation, finalRot, duration, type, loop, callback);
}

void TweenComponent::easeRotation(float finalRot, b2Vec2 pivotPoint, float duration, tween::tweenType type,bool loop, Callback callback){
    b2Vec2 initialPos = _myTr->getPosition();
    float initialRot = _myTr->getRotation();
    b2Vec2 v = initialPos-pivotPoint;
    easeValue(&_myTr->_rotation, _myTr->_rotation + finalRot, duration, type, loop, callback, [=](){
        float diffAngle = initialRot-_myTr->getRotation();
        float diffRad = diffAngle * M_PI/180;

        b2Vec2 rotatedVector = {v.x*cos(diffRad) - v.y*sin(diffRad), v.x*sin(diffRad) + v.y*cos(diffRad)};
        _myTr->setPosition(pivotPoint + rotatedVector);
    });
}

void TweenComponent::easeScale(float finalScale, float duration, tween::tweenType type,bool loop , Callback callback ){
    easeValue(&_myEntity->getComponent<RenderTextureComponent>()->_scale, finalScale, duration, type, loop, callback);
}

void TweenComponent::eraseAllTweens(){
    for(auto t : _tweens) delete t;
    _tweens.resize(0);
}