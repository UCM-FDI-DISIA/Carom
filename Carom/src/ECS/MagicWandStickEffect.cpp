#include "MagicWandStickEffect.h"
#include "CaromScene.h"
#include "ITransform.h"
#include "RigidBodyComponent.h"
#include "RenderTextureComponent.h"
#include "SubdivisionEffect.h"
#include "StickInputComponent.h"
#include <box2d/box2d.h>


void
MagicWandStickEffect::applyEffect(entity_t target){
    CaromScene* a_scene = static_cast<CaromScene*>(&target->getScene());
    ITransform* a_targetTransform = dynamic_cast<ITransform*>(target->getTransform());
    RigidBodyComponent* a_targetRB = dynamic_cast<RigidBodyComponent*>(target->getComponent<RigidBodyComponent>());
    assert(a_targetRB != nullptr && a_scene != nullptr && a_targetTransform != nullptr);
    
    
    //TODO Hacer que se pueda añadir la subdivision al grupo de efectos de la bola original
    auto a_ball1 = a_scene->createWhiteBall(a_targetTransform->getPosition(), 
    a_targetRB->getBodyType(), a_targetRB->getDensity(), 
    a_targetRB->getFriction(), a_targetRB->getRestitution());
    
    auto a_ball2 = a_scene->createWhiteBall(a_targetTransform->getPosition(), 
    a_targetRB->getBodyType(), a_targetRB->getDensity(), 
    a_targetRB->getFriction(), a_targetRB->getRestitution());

    _myEntity->getComponent<StickInputComponent>()->registerWhiteBall(target); //* Reset the right wb
    
    a_ball1->addComponent<SubdivisionEffect>(new SubdivisionEffect(a_ball1, target));
    a_ball2->addComponent<SubdivisionEffect>(new SubdivisionEffect(a_ball2, target));
    
    RigidBodyComponent* a_1RB = dynamic_cast<RigidBodyComponent*>(a_ball1->getComponent<RigidBodyComponent>());
    RigidBodyComponent* a_2RB = dynamic_cast<RigidBodyComponent*>(a_ball2->getComponent<RigidBodyComponent>());

    b2Rot rotation1 = b2MakeRot(M_PI/4);
    b2Rot rotation2 = b2MakeRot(7*M_PI/4);

    a_1RB->applyForceToCenter(b2RotateVector(rotation1, a_targetRB->getVelocity()));
    a_2RB->applyForceToCenter(b2RotateVector(rotation2, a_targetRB->getVelocity()));

    target->deactivate();
}