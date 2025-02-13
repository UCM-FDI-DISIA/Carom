// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

namespace ecs {

Manager::Manager()
{
}

Manager::~Manager() 
{
}

void
Manager::update(){
    for (auto* e : entities){
        e->update();
    }
}

void
Manager::render(){
    for (auto* e : entities){
        e->render();
    }
}

} // end of namespace
