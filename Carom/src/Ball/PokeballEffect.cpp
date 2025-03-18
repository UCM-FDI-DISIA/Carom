#pragma once
#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include <vector>

void PokeballEffect::onHit(ecs::entity_t ent)
{
    std::vector effects = ent->getComponent<BallHandler>()->getEffects();

    for(Component* comp : effects)
    {
        // ent->addComponent(comp);
        // ent->removeComponent(&comp);
    }

    effects.clear();
    ent->removeComponent<PokeballEffect>();
};