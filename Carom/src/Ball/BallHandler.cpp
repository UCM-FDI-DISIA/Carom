#include "BallHandler.h"
#include "Entity.h"
#include "BallEffect.h"
#include "CaromScene.h"

void BallHandler::init()
{
    _scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
    assert(_scene != nullptr && "Se ha intentado agregar un componente de efecto en una escena que no es la de juego");
}

void BallHandler::onCollisionEnter(entity_t collision)
{
    if(collision->getID() == grp::EFFECTBALLS || collision->getID() == grp::WHITEBALL)
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

void BallHandler::onBeingTargeted()
{
    for(BallEffect* effect : _effects)
    {
        effect->onBeingTargeted();
    }
}

void BallHandler::addScore(float points)
{
    _scene->addScore(points);
}

void BallHandler::multScore(float mult)
{
    _scene->addScore(_scene->getCurrentScore() * (mult - 1));
}

void BallHandler::setMult(float newMult)
{
    _mult = newMult;
    
    for(BallEffect* effect : _effects)
    {
        effect->onMultChanged();
    }
}

bool BallHandler::addEffect(BallEffect* effect)
{
    if(_effects.size() < EFFECTS_LIMIT)
    {
        _effects.push_back(effect);
        return true;
    } else return false;
}