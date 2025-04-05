#pragma once
#include "HandleEventComponent.h"

class UnpauseComponent: public HandleEventComponent{
    public:
    __CMPID_DECL__(cmp::UNPAUSE);

    inline UnpauseComponent(Entity* e) : HandleEventComponent(e){}

    void handleEvent() override;
    inline void init() override{}
};