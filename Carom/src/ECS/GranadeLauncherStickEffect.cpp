#include "GranadeLauncherStickEffect.h"
#include "ExplosiveEffect.h"
#include "Entity.h"

namespace ecs {

    GranadeLauncherStickEffect::GranadeLauncherStickEffect(entity_t ent, float force, float explosionDelay, float radius) : StickEffectComponent(ent), _explosionForce(force), _explosionDelay(explosionDelay), _radius(radius)
    {
    }

    GranadeLauncherStickEffect::~GranadeLauncherStickEffect() {}

    void 
    GranadeLauncherStickEffect::init(){

    } 

    void 
    GranadeLauncherStickEffect::applyEffect(entity_t ball){
       ball->addComponent<ExplosiveEffect>(new ExplosiveEffect(ball, _explosionDelay, _radius, _explosionForce));
    } 
}