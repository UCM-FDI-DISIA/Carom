#include "EntityManager.h"

namespace ecs {

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager() 
{
    for (auto* e : _entities)
        delete e;
}

int
EntityManager::addEntity() {
    int id = _id;
    _id++; // increments count;

    entity_t e = new Entity();
    _entities.push_back(std::move(e));

    return id;
}

int
EntityManager::addEntity(obj::objId objId) {
    int id = _id;
    _id++; // increments count;

    switch (objId){
        case (obj::WHITEBALL): {
            entity_t e = new Entity();
            addComponent<TransformComponent>(e);
            addComponent<RenderTextureComponent>(e, &sdlutils().images().at("tennis_ball"));
            _entities.push_back(std::move(e));
            break;
        }
        // TODO: restantes
    }

    return id;
}

void
EntityManager::update(){
    for (auto* e : _entities)
        e->update();
}

void
EntityManager::render(){
    for (auto* e : _entities)
        e->render();
}

} // end of namespace
