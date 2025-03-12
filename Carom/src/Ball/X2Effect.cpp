#pragma once
#include "X2Effect.h"
#include "BallHandler.h"
#include "Entity.h"

void X2Effect::init()
{
    _myEntity->getComponent<BallHandler>()->setMult(2);
}