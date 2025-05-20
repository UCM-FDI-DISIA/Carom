#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include "RenderSpritesheetComponent.h"
#include <vector>
#include "SDLUtils.h"

//Se ejecuta cuando es golpeada, roba todos los efectos de la bola con la que colisiona
void PokeballEffect::onHit(entity_t ent)
{
    if(ent->getID() == grp::WHITEBALL) return;
    std::vector effects = ent->getComponent<BallHandler>()->getEffects();
    if(effects.size() == 0) return;

    RenderSpritesheetComponent* renderCmp = _myEntity->getComponent<RenderSpritesheetComponent>();
    if(renderCmp == nullptr) return;

    Texture* texture = ent->getComponent<RenderSpritesheetComponent>()->getTexture();
    
    for(BallEffect* effect : effects)
    {
        _myEntity->stealComponent(ent, effect);
    }
    
    ent->getComponent<BallHandler>()->removeAllEffects();
    _myEntity->getComponent<BallHandler>()->breakHit();

    //Actualiza la textura de la bola y se elimina la pokeball
    _myEntity->getComponent<RenderSpritesheetComponent>()->setTexture(texture);
    ent->getComponent<RenderSpritesheetComponent>()->setTexture(&sdlutils().images().at("Ignacio"));
    _myEntity->removeComponent<PokeballEffect>();
};