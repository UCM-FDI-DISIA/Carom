#include "MagicWandStickEffect.h"
#include "CaromScene.h"
#include "ITransform.h"
#include "RigidBodyComponent.h"

using namespace ecs;

void
MagicWandStickEffect::applyEffect(entity_t ent){
    CaromScene* a_scene = static_cast<CaromScene*>(&ent->getScene());
    ITransform* a_targetTransform = dynamic_cast<ITransform*>(ent->getTransform());
    RigidBodyComponent* a_targetRB = dynamic_cast<RigidBodyComponent*>(ent->getComponent<RigidBodyComponent>());

    assert(a_targetRB != nullptr && a_scene != nullptr && a_targetTransform != nullptr);

    //TODO Hacer que se pueda añadir la subdivision al grupo de efectos de la bola original
    auto a_ball1 = a_scene->createEffectBall(ecs::effect::NULO, a_targetTransform->getPosition(), 
                            a_targetRB->getBodyType(), a_targetRB->getDensity(), 
                            a_targetRB->getFriction(), a_targetRB->getRestitution());
    
    auto a_ball2 = a_scene->createEffectBall(ecs::effect::NULO, a_targetTransform->getPosition(), 
                            a_targetRB->getBodyType(), a_targetRB->getDensity(), 
                            a_targetRB->getFriction(), a_targetRB->getRestitution());
    
    
}