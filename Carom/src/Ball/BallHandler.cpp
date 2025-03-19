#include "BallHandler.h"
#include "Entity.h"
#include "BallEffect.h"
#include "CaromScene.h"

using namespace ecs;

void BallHandler::init()
{
    _scene = dynamic_cast<ecs::CaromScene*>(&_myEntity->getScene());
    assert(_scene != nullptr && "Se ha intentado agregar un componente de efecto en una escena que no es la de juego");
}

void BallHandler::onCollisionEnter(ecs::entity_t collision)
{
    if(collision->getID() == ecs::grp::EFFECTBALLS || collision->getID() == ecs::grp::WHITEBALL)
    {
        for(ecs::BallEffect* effect : _effects)
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

void BallHandler::onBeingTargeted()
{
    for(BallEffect* effect : _effects)
    {
        effect->onBeingTargeted();
    }
}

void BallHandler::addScore(float points)
{
    _scene->addScore(points * _mult);
}

void BallHandler::multScore(float mult)
{
    _scene->addScore(_scene->getCurrentScore() * ((mult * _mult) - 1));
}