#include "CameraComponent.h"
#include "PhysicsUtils.h"
#include "Entity.h"
#include "ITransform.h"
#include "GameScene.h"
#include "TweenComponent.h"


std::pair<int,int> CameraComponent::getRenderPos(b2Vec2 physicalPos){
    float resX,resY;
    resX = physicalPos.x - _myEntity->getTransform()->getPosition().x;
    resY = physicalPos.y - _myEntity->getTransform()->getPosition().y;

    std::pair<int,int> res = PhysicsConverter::meter2pixel({resX,resY});

    return res;
}
CameraComponent::CameraComponent(Entity* e): InfoComponent(e){
}

void CameraComponent::shakeCamera(float intensity, float duration, Vector2D dir){
    TweenComponent* tween = _myEntity->getComponent<TweenComponent>();
    if(!tween->isTweening()){
        ITransform* transform = _myEntity->getTransform();
        b2Vec2 pos = transform->getPosition();
        
        tween->easePosition({pos.x+ dir.getX()*intensity, pos.y+ dir.getY()*intensity}, duration*0.1f, tween::EASE_OUT_QUINT, false, [=](){
            tween->easePosition({pos.x, pos.y}, duration*0.9f, tween::EASE_OUT_ELASTIC);
        });
    }
    
}
