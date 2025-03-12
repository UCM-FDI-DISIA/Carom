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

void TweenManager::linearTransformMovement(ecs::TransformComponent* tr, Vector2D finalPos, float duration){
    LinearTween* tX = new LinearTween(this, &tr->_position.x, finalPos.getX(), uint32_t(duration*1000));
    LinearTween* tY = new LinearTween(this, &tr->_position.y, finalPos.getY(), uint32_t(duration*1000));

    _tweens.push_back(tX);
    _tweens.push_back(tY);
}

void TweenManager::easeInBackTransformMovement(ecs::TransformComponent* tr, Vector2D finalPos, float duration){
    EaseInBackTween* tX = new EaseInBackTween(this, &tr->_position.x, finalPos.getX(), uint32_t(duration*1000));
    EaseInBackTween* tY = new EaseInBackTween(this, &tr->_position.y, finalPos.getY(), uint32_t(duration*1000));

    _tweens.push_back(tX);
    _tweens.push_back(tY);
}