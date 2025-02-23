#include "ColorBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "CaromScene.h"
#include "ColorHitManager.h"

namespace ecs{
    void ColorBallScorerComponent::init(){
        _myEntity->getComponent<RigidBodyComponent>()->setOnCollisionEnter([this](entity_t other){
            CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
            if(a_scene != nullptr){
                
            }
        });
    }
}