#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include "RenderSpritesheetComponent.h"
#include <vector>
#include "SDLUtils.h"

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

    BallEffect* firstEffect = _myEntity->getComponent<BallHandler>()->getEffects()[0];
    _myEntity->getComponent<RenderSpritesheetComponent>()->setTexture(&sdlutils().images().at(BallEffect::effectTextureName(firstEffect)));

    _myEntity->removeComponent<PokeballEffect>();
};