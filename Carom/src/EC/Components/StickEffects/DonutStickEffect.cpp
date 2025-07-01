#include "DonutStickEffect.h"
#include "PopToOppositeSideEffect.h"
#include "EventOnCollision.h"
#include "Entity.h"

#include "StickInputComponent.h"
#include "AudioManager.h"


void
DonutStickEffect::applyEffect(entity_t target){

    AudioManager::Instance()->playSoundEfect("donut");
    auto ballHandler = target->getComponent<BallHandler>();
    auto popComp = new PopToOppositeSideEffect(ballHandler);
    ballHandler->addEffect<PopToOppositeSideEffect>(popComp);

    auto EvtColl = new EventOnCollision(target, [this, popComp](entity_t other, b2Manifold& contactData){popComp->popOnCollision(other);}, [](entity_t){} );
    target->addComponent<EventOnCollision>(EvtColl);
}