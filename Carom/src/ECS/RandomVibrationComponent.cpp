#include "RandomVibrationComponent.h"
#include "TweenComponent.h"
#include "Entity.h"
#include "GameScene.h"
#include <cstdlib>

RandomVibrationComponent::RandomVibrationComponent(entity_t e, float intensity, float speed): LogicComponent(e){
    _intensity = intensity;
    _speed = speed;
}

void RandomVibrationComponent::init(){
    _anchoredPosition = _myEntity->getTransform()->getPosition();
    TweenComponent* tween;
    if(!_myEntity->tryGetComponent(tween)){
        tween = new TweenComponent(_myEntity);
        _myEntity->addComponent(tween);
    }
    nextRandomPos = [=](){
        float rX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        rX = rX *_intensity*2;

        if(rX > _intensity) rX = rX - _intensity;
        else rX = -(rX-_intensity);

        float rY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        rY = rY *_intensity*2;

        if(rY > _intensity) rY = rY - _intensity;
        else rY = -(rY-_intensity);

        b2Vec2 finalPos = {_anchoredPosition.x + rX, _anchoredPosition.y + rY};

        tween->easePosition(finalPos, _speed, tween::EASE_IN_OUT_CUBIC, false, nextRandomPos);
    };

    nextRandomPos();

}