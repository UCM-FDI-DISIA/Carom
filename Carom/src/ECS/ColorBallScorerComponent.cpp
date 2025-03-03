#include "ColorBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "CaromScene.h"
#include "ColorHitManager.h"

namespace ecs{
    ColorBallScorerComponent::ColorBallScorerComponent(entity_t ent): PhysicsComponent(ent) {
        
    }
    
    void ColorBallScorerComponent::onCollisionEnter(entity_t other){
        // si choca con una bola de color...
        if(other->tryGetComponent<ColorBallScorerComponent>()){
            CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
            if(a_scene == nullptr) return;
            // procesa el hit de las entidades colisionadas por medio del getColorHitManager en la escena CaromScene.
            a_scene->getColorHitManager()->processHitEntities(_myEntity, other);
        }
    }
}