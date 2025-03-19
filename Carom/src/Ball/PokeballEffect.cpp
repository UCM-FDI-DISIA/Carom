#pragma once
#include "PokeballEffect.h"
#include "BallHandler.h"
#include "Entity.h"
#include <iostream>
#include<vector>
using namespace ecs;

void PokeballEffect::onHit(ecs::entity_t ent)
{
    std::vector effects = ent->getComponent<BallHandler>()->getEffects();
    for(Component* comp : effects)
    {
        std::cout << "Pokeball absorbe efecto: " << typeid(comp).name() << std:: endl;
        // ent->addComponent(comp);
        // ent->removeComponent(&comp);
    }
}

void PokeballEffect::init()
{

}