#include "ColorBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "CaromScene.h"
#include "ColorHitManager.h"

namespace ecs{
    void ColorBallScorerComponent::init(){
        _myEntity->getComponent<RigidBodyComponent>()->setOnCollisionEnter([this](entity_t other){
            if(other->tryGetComponent<ColorBallScorerComponent>()){
                CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
            if(a_scene != nullptr){
                a_scene->getColorHitManager()->processHitEntities(_myEntity, other);
            }
            }
            
        });
    }
}