#include "BoxingGloveStickEffect.h"
#include "FrictionMultiplierEffect.h"
#include "Entity.h"


BoxingGloveStickEffect::BoxingGloveStickEffect(entity_t entity, float factor)  : StickEffectComponent(entity), _factor(factor)
{
}

BoxingGloveStickEffect::~BoxingGloveStickEffect() {}

void
BoxingGloveStickEffect::applyEffect(entity_t target) {
    target->addComponent<FrictionMultiplierEffect>(new FrictionMultiplierEffect(target, _factor));
}

