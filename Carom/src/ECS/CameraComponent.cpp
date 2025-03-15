#include "CameraComponent.h"
#include "PhysicsUtils.h"
#include "Entity.h"
#include "ITransform.h"
#include "GameScene.h"

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
}
