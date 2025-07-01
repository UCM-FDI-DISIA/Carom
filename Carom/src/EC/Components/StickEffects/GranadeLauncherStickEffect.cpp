#include "GranadeLauncherStickEffect.h"
#include "ExplosiveEffect.h"
#include "Entity.h"


GranadeLauncherStickEffect::GranadeLauncherStickEffect(entity_t ent, float force, float explosionDelay, float radius) : StickEffectComponent(ent), _explosionForce(force), _explosionDelay(explosionDelay), _radius(radius)
{
}

GranadeLauncherStickEffect::~GranadeLauncherStickEffect() {}

void 
GranadeLauncherStickEffect::applyEffect(entity_t ball){
    auto ballHandler = ball->getComponent<BallHandler>();
    ballHandler->addEffect<ExplosiveEffect>(new ExplosiveEffect(ballHandler, _explosionDelay, _radius, _explosionForce));
} 
