#pragma once
#include "HandleEventComponent.h"

class TweenComponent;
class UnpauseComponent: public HandleEventComponent{
    TweenComponent* tween;
    public:
    __CMPID_DECL__(cmp::UNPAUSE);

    inline UnpauseComponent(Entity* e, TweenComponent* t) : HandleEventComponent(e), tween(t){}

    void handleEvent() override;
    inline void init() override{}
};