#include "CameraComponent.h"
#include "PhysicsUtils.h"
#include "Entity.h"
#include "ITransform.h"
#include "GameScene.h"
#include "TweenComponent.h"

namespace ecs{
    std::pair<int,int> CameraComponent::getRenderPos(b2Vec2 physicalPos){
        float resX,resY;
        resX = physicalPos.x - _myEntity->getTransform()->getPosition().x;
        resY = physicalPos.y - _myEntity->getTransform()->getPosition().y;
    
        std::pair<int,int> res = PhysicsConverter::meter2pixel({resX,resY});
    
        return res;
    }
    CameraComponent::CameraComponent(Entity* e): InfoComponent(e){
    }

    void CameraComponent::shakeCamera(float intensity, float duration){
        ITransform* transform = _myEntity->getTransform();
        b2Vec2 pos = transform->getPosition();
        TweenComponent* tween = _myEntity->getComponent<TweenComponent>();
        transform->setPosition(b2Vec2{pos.x, pos.y + intensity});
        tween->easePosition({pos.x, pos.y}, duration, tween::EASE_OUT_ELASTIC);
    }
}
