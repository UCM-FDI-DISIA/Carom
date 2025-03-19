#pragma once
#include "X2Effect.h"
#include "BallHandler.h"
#include "Entity.h"

void X2Effect::init()
{
    BallEffect::init();
    _handler->setMult(2);
}