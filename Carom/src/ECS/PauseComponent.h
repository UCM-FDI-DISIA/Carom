#pragma once
#include "HandleEventComponent.h"

class PauseComponent: public HandleEventComponent{
    public:
    __CMPID_DECL__(cmp::PAUSE);

    PauseComponent(Entity* e) : HandleEventComponent(e){}

    void handleEvent() override;
    inline void init() override{}
};