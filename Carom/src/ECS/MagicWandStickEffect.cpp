#include "MagicWandStickEffect.h"
#include "CaromScene.h"
#include "ITransform.h"
#include "RigidBodyComponent.h"
#include "RenderTextureComponent.h"
#include "SubdivisionEffect.h"
#include <box2D/box2D.h>

using namespace ecs;

void
MagicWandStickEffect::applyEffect(entity_t target){
    CaromScene* a_scene = static_cast<CaromScene*>(&target->getScene());
    ITransform* a_targetTransform = dynamic_cast<ITransform*>(target->getTransform());
    RigidBodyComponent* a_targetRB = dynamic_cast<RigidBodyComponent*>(target->getComponent<RigidBodyComponent>());
    RenderTextureComponent* comp;
    int layer = target->tryGetComponent<RenderTextureComponent>(comp) 
    ?comp->renderOrder
    :0;
    assert(a_targetRB != nullptr && a_scene != nullptr && a_targetTransform != nullptr);
    
    
    //TODO Hacer que se pueda añadir la subdivision al grupo de efectos de la bola original
    auto a_ball1 = a_scene->createEffectBall(ecs::effect::NULO, a_targetTransform->getPosition(), 
    a_targetRB->getBodyType(), a_targetRB->getDensity(), 
    a_targetRB->getFriction(), a_targetRB->getRestitution(), layer);
    
    auto a_ball2 = a_scene->createEffectBall(ecs::effect::NULO, a_targetTransform->getPosition(), 
    a_targetRB->getBodyType(), a_targetRB->getDensity(), 
    a_targetRB->getFriction(), a_targetRB->getRestitution(), layer);
    
    SubdivisionEffect* a_sb = new SubdivisionEffect(a_ball1, target);
    a_ball1->addComponent<SubdivisionEffect>(a_sb); //! AQUI SE CAGA ENCIMA
    //a_sb = new SubdivisionEffect(a_ball2, target);
    //a_ball2->addComponent<SubdivisionEffect>(a_sb);
    //a_sb = nullptr;
    
    RigidBodyComponent* a_1RB = dynamic_cast<RigidBodyComponent*>(a_ball1->getComponent<RigidBodyComponent>());
    RigidBodyComponent* a_2RB = dynamic_cast<RigidBodyComponent*>(a_ball2->getComponent<RigidBodyComponent>());

    a_1RB->applyForceToCenter(b2CrossVS(a_targetRB->getVelocity(), 1/sqrt(2)));
    a_2RB->applyForceToCenter(b2CrossVS(a_targetRB->getVelocity(), -1/sqrt(2)));

    target->deactivate();
    std::cout << "Termina\n";
}