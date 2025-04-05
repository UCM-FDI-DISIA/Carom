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
        _myEntity->addComponent<BallEffect>(effect);
        ent->removeComponent(effect);
    }

    effects.clear();
    _myEntity->removeComponent<PokeballEffect>();
};