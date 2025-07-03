#include "GranadeLauncherStickEffect.h"
#include "ExplosiveEffect.h"
#include "Entity.h"


GranadeLauncherStickEffect::GranadeLauncherStickEffect(entity_t ent) : StickEffectComponent(ent)
{
}

GranadeLauncherStickEffect::~GranadeLauncherStickEffect() {}

void 
GranadeLauncherStickEffect::applyEffect(entity_t ball){
    auto ballHandler = ball->getComponent<BallHandler>();
    ballHandler->addEffect<ExplosiveEffect>(new ExplosiveEffect(ballHandler, EXPLOSION_DELAY, EXPLOSION_RADIUS, EXPLOSION_FORCE));
} 
