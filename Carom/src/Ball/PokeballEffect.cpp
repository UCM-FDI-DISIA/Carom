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

    RenderSpritesheetComponent* renderCmp = _handler->_myEntity->getComponent<RenderSpritesheetComponent>();
    if(renderCmp == nullptr) return;

    Texture* texture = ent->getComponent<RenderSpritesheetComponent>()->getTexture();
    
    for(BallEffect* effect : effects)
    {
        _handler->_myEntity->stealComponent(ent, effect);
    }
    
    ent->getComponent<BallHandler>()->removeAllEffects();
    _handler->_myEntity->getComponent<BallHandler>()->breakHit();

    //Actualiza la textura de la bola y se elimina la pokeball
    _handler->_myEntity->getComponent<RenderSpritesheetComponent>()->setTexture(texture);
    //ent->getComponent<RenderSpritesheetComponent>()->setTexture(&sdlutils().images().at("Ignacio")); a tomar por culo ignacio
    _handler->_myEntity->removeComponent<PokeballEffect>();
};