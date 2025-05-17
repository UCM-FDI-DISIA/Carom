#include "DonutStickEffect.h"
#include "PopToOppositeSideEffect.h"
#include "EventOnCollision.h"
#include "Entity.h"

#include "StickInputComponent.h"
#include "AudioManager.h"


void
DonutStickEffect::applyEffect(entity_t target){

    AudioManager::Instance()->playSoundEfect("donut", 90);
    auto popComp = new PopToOppositeSideEffect(target);
    target->addComponent<PopToOppositeSideEffect>(popComp);

    auto EvtColl = new EventOnCollision(target, [this, popComp](entity_t other, b2Manifold& contactData){popComp->popOnCollision(other);}, [](entity_t){} );
    target->addComponent<EventOnCollision>(EvtColl);
}