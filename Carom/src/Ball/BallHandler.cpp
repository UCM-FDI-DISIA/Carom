#include "BallHandler.h"
#include "Entity.h"
#include "BallEffect.h"
#include "CaromScene.h"

void BallHandler::init()
{
}

void BallHandler::onCollisionEnter(ecs::entity_t collision)
{
    if(collision->getID() == ecs::grp::EFFECTBALLS || collision->getID() == ecs::grp::WHITEBALL)
    {
        for(BallEffect* effect : _effects)
        {
            effect->onHit(collision);
        }
    }
}

void BallHandler::onStrikeEnd()
{
    for(BallEffect* effect : _effects)
    {
        effect->onStrikeEnd();
    }
}