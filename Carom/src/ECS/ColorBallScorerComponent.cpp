#include "ColorBallScorerComponent.h"
#include "Entity.h"
#include "GameScene.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
#include "WallComponent.h"
#include "AudioManager.h"

ColorBallScorerComponent::ColorBallScorerComponent(entity_t ent) : PhysicsComponent(ent) {}

void ColorBallScorerComponent::onCollisionEnter(entity_t other, b2Manifold& contactData){
    if(other->tryGetComponent<WallComponent>()) AudioManager::Instance()->playSoundEfect("wall_hit");
    // si choca con una bola de color...
    if(other->tryGetComponent<ColorBallScorerComponent>()){
        
        CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
        if(a_scene == nullptr) return;
        // procesa el hit de las entidades colisionadas por medio del getColorHitManager en la escena CaromScene.
        a_scene->getColorHitManager()->processHitEntities(_myEntity, other);
    }
}