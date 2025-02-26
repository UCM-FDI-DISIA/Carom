#include "Tweening.h"

void TweenSystem::addTween(float* initialValue, float endValue,float time, TweenType type, int loop){
    Tween tween = {initialValue, endValue, time, endValue - *initialValue, type, loop};

    _currentTweens.push_back(tween);
}

void TweenSystem::updateValues(){
    for(auto tween : _currentTweens){
        switch (tween.type){
            case LINEAR:
            
            break;
            case POW_IN:

            break;
            case POW_OUT:

            break;
            case POW_IN_OUT:

            break;
        }
            
    }
}