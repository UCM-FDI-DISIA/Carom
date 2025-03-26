#include "DonutStickEffect.h"
#include "ShowAtOppositeSideComponent.h"
#include "Entity.h"

void
DonutStickEffect::applyEffect(entity_t target){
    target->addComponent<ShowAtOppositeSideComponent>(new ShowAtOppositeSideComponent(target));
}