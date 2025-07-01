#include "BallHandler.h"
#include "Entity.h"
#include "BallEffect.h"
#include "CaromScene.h"


#include "AbacusEffect.h"
#include "BowlingEffect.h"
#include "CristalEffect.h"
#include "QuanticEffect.h"
#include "PetanqueEffect.h"
#include "X2Effect.h"

void BallHandler::init()
{
    _scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
}

void BallHandler::onCollisionEnter(entity_t collision, b2Manifold& contactData)
{
    if(collision->getID() == grp::EFFECTBALLS || collision->getID() == grp::WHITEBALL)
    {
        for(BallEffect* effect : _effects)
        {
            effect->onHit(collision);
            if(_breakHit)
            {
                _breakHit = false;
                break;
            }
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

void BallHandler::multRoundScore(float mult){
    _scene->addScore(_scene->getRoundScore() * (mult - 1));
}

void BallHandler::setMult(float newMult)
{
    _mult = newMult;
    
    for(BallEffect* effect : _effects)
    {
        effect->onMultChanged();
    }
}

bool
BallHandler::internalAddEffect(effectId_t id, BallEffect* component, bool initCmp) {
    if(_effects[id] != nullptr) return false;

    _effects[id] = component;
    _currentEffects.push_back(component);

    if (initCmp) 
        _effects[id]->init();

    return true;
}

bool
BallHandler::internalRemoveEffect(effectId_t id, bool deleteCmp) {
    if(_effects[id] == nullptr) return false;

    auto it = find(_currentEffects.begin(), _currentEffects.end(), _effects[id]);
    _currentEffects.erase(it);

    if (deleteCmp)
        delete _effects[id];

    _effects[id] = nullptr;

    return true;
}

std::vector<effectId_t> BallHandler::getEffectsID(){
    std::vector<effectId_t> res;
    for(auto effect : _currentEffects){
        res.push_back(effect->getEffectId());
    }

    return res;
}


void BallHandler::removeAllEffects(){
    for(auto effect : _effects){
        if(effect != nullptr) delete effect;
    }

    _currentEffects.clear();
}
