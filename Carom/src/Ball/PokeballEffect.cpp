#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include <vector>

void PokeballEffect::onHit(entity_t ent)
{
    std::vector effects = ent->getComponent<BallHandler>()->getEffects();
    if(effects.size() == 0) return;
    
    for(BallEffect* effect : effects)
    {
        _myEntity->stealComponent(ent, effect);
    }
    
    ent->getComponent<BallHandler>()->removeAllEffects();
    _myEntity->getComponent<BallHandler>()->breakHit();
    _myEntity->removeComponent<PokeballEffect>();
};