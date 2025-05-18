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

    Texture* texture = ent->getComponent<RenderSpritesheetComponent>()->getTexture();
    
    for(BallEffect* effect : effects)
    {
        _myEntity->stealComponent(ent, effect);
    }
    
    ent->getComponent<BallHandler>()->removeAllEffects();
    _myEntity->getComponent<BallHandler>()->breakHit();

    
    _myEntity->getComponent<RenderSpritesheetComponent>()->setTexture(texture);
    ent->getComponent<RenderSpritesheetComponent>()->setTexture(&sdlutils().images().at("Ignacio"));
    _myEntity->removeComponent<PokeballEffect>();
};