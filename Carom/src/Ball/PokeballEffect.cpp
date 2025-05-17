#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include <vector>

void PokeballEffect::onHit(entity_t ent)
{
    _myEntity->removeComponent<PokeballEffect>();
    std::vector effects = ent->getComponent<BallHandler>()->getEffects();

    for(BallEffect* effect : effects)
    {
        _myEntity->stealComponent(ent, effect);
        // _myEntity->addComponent<BallEffect>(effect);
        // ent->removeComponent(effect);
    }

    // effects.clear();
    // _myEntity->getComponent<BallHandler>()->removeAllEffects();
};