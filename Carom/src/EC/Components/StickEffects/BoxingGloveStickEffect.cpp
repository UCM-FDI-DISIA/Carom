#include "BoxingGloveStickEffect.h"
#include "FrictionMultiplierEffect.h"
#include "Entity.h"
#include "AudioManager.h"


BoxingGloveStickEffect::BoxingGloveStickEffect(entity_t entity)  : StickEffectComponent(entity)
{
}

BoxingGloveStickEffect::~BoxingGloveStickEffect() {}

void
BoxingGloveStickEffect::applyEffect(entity_t target) {
    AudioManager::Instance()->playSoundEfect("boxing");
    auto ballHandler = target->getComponent<BallHandler>();
    ballHandler->addEffect<FrictionMultiplierEffect>(new FrictionMultiplierEffect(ballHandler, FRICTION_FACTOR));
}

