#pragma once
#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include <vector>

void PokeballEffect::onHit(entity_t ent)
{
    std::vector effects = ent->getComponent<BallHandler>()->getEffects();

    for(BallEffect* effect : effects)
    {
        ent->addComponent(effect, effect->getEffectId());
        ent->removeComponent(effect->getEffectId());
    }

    effects.clear();
    ent->removeComponent<PokeballEffect>();
};