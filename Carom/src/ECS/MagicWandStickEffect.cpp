#include "MagicWandStickEffect.h"
#include "CaromScene.h"
#include "ITransform.h"
#include "RigidBodyComponent.h"
#include "RenderTextureComponent.h"
#include "SubdivisionEffect.h"
#include <box2D/box2D.h>

using namespace ecs;

void
MagicWandStickEffect::applyEffect(entity_t ent){
    CaromScene* a_scene = static_cast<CaromScene*>(&ent->getScene());
    ITransform* a_targetTransform = dynamic_cast<ITransform*>(ent->getTransform());
    RigidBodyComponent* a_targetRB = dynamic_cast<RigidBodyComponent*>(ent->getComponent<RigidBodyComponent>());
    RenderTextureComponent* comp;
    int layer = ent->tryGetComponent<RenderTextureComponent>(comp) 
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

    SubdivisionEffect* a_sb1 = new SubdivisionEffect(a_ball1, ent);
    a_ball1->addComponent<SubdivisionEffect>(a_sb1);
    SubdivisionEffect* a_sb2 = new SubdivisionEffect(a_ball2, ent);
    a_ball2->addComponent<SubdivisionEffect>(a_sb2);
    
    RigidBodyComponent* a_1RB = dynamic_cast<RigidBodyComponent*>(a_ball1->getComponent<RigidBodyComponent>());
    RigidBodyComponent* a_2RB = dynamic_cast<RigidBodyComponent*>(a_ball2->getComponent<RigidBodyComponent>());

    a_1RB->applyForceToCenter(b2CrossVS(a_targetRB->getVelocity(), 1/sqrt(2)));
    a_2RB->applyForceToCenter(b2CrossVS(a_targetRB->getVelocity(), -1/sqrt(2)));

    ent->deactivate();
}