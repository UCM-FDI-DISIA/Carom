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

bool BallHandler::addEffect(effectId_t effect)
{
    if(_effects.size() < EFFECTS_LIMIT)
    {
        switch(effect){
            case effect::ABBACUS: _myEntity->addComponent<AbacusEffect>(new AbacusEffect(_myEntity)); break;
            case effect::BOWLING: _myEntity->addComponent<BowlingEffect>(new BowlingEffect(_myEntity)); break;
            case effect::CRISTAL: _myEntity->addComponent<CristalEffect>(new CristalEffect(_myEntity)); break;
            case effect::QUANTIC: _myEntity->addComponent<QuanticEffect>(new QuanticEffect(_myEntity)); break;
            case effect::PETANQUE: _myEntity->addComponent<PetanqueEffect>(new PetanqueEffect(_myEntity)); break;
            case effect::X2: _myEntity->addComponent<X2Effect>(new X2Effect(_myEntity)); break;
        }
        _effectIds.push_back(effect);
        return true;
    } else return false;
}

bool BallHandler::removeEffect(effectId_t effectType) {
    BallEffect* effect;

    switch(effectType){
            case effect::ABBACUS: effect = _myEntity->getComponent<AbacusEffect>(); break;
            case effect::BOWLING: effect = _myEntity->getComponent<BowlingEffect>(); break;
            case effect::CRISTAL: effect = _myEntity->getComponent<CristalEffect>(); break;
            case effect::QUANTIC: effect = _myEntity->getComponent<QuanticEffect>(); break;
            case effect::PETANQUE: effect = _myEntity->getComponent<PetanqueEffect>(); break;
            case effect::X2: effect = _myEntity->getComponent<X2Effect>(); break;
        }
    if(effect = nullptr) return true;

    auto it = find(_effects.begin(), _effects.end(), effect);
    _effects.erase(it);

    auto it2 = find(_effectIds.begin(), _effectIds.end(), effectType);
    _effectIds.erase(it2);

    return true;
}

void BallHandler::removeAllEffects(){
    _effects.clear();
}
