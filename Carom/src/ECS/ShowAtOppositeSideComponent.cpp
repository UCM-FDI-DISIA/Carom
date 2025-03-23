#pragma once

#include "ShowAtOppositeSideComponent.h"
#include "WallComponent.h"
#include "Entity.h"

using namespace ecs;

void
ShowAtOppositeSideComponent::onCollisionEnter(entity_t ent){
    if(!ent->tryGetComponent<WallComponent>()) return;

    // TODO Que aparezca al lado opuesto
}