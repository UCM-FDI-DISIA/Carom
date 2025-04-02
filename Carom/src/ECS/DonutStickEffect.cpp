#include "DonutStickEffect.h"
#include "PopToOppositeSideEffect.h"
#include "EventOnCollision.h"
#include "Entity.h"

using namespace ecs;

void
DonutStickEffect::applyEffect(entity_t target){
    auto popComp = new PopToOppositeSideEffect(target);
    target->addComponent<PopToOppositeSideEffect>(popComp);

    auto EvtColl = new EventOnCollision(target, [this, popComp](entity_t other){popComp->popOnCollision(other);}, [](entity_t){} );
    target->addComponent<EventOnCollision>(EvtColl);
}