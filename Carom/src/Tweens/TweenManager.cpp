#include "TweenManager.h"
#include "Tween.h"

TweenManager::TweenManager(){
    _paused = false;
}

void TweenManager::update(){
    if(!_paused){
        for(Tween* t: _tweens){
            t->update();
        }
    }
    
    //si se han acabado algunas, se matan
    std::remove_if(_tweens.begin(), _tweens.end(), [this](Tween* e){
        if(e->isAlive()) return false;
        return true;
    });
}

void TweenManager::removeTween(Tween* t){
    t->setAlive(false);
}

void TweenManager::pauseTweening() { _paused = true;}
void TweenManager::resumeTweening() { _paused = false;}