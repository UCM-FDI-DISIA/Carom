#include "EntityManager.h"

namespace ecs {

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager() 
{
}

void
EntityManager::update(){
    for (auto* e : entities){
        e->update();
    }
}

void
EntityManager::render(){
    for (auto* e : entities){
        e->render();
    }
}

} // end of namespace
