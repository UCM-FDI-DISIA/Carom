#include "EntityManager.h"

namespace ecs {

EntityManager::EntityManager(GameList<Entity> *entities) 
    : _GS_entities(entities)
{
}

EntityManager::~EntityManager() 
{
    // ! POR LA GAMELIST ES NECESARIO???
    for (auto* e : _entities)
        delete e;
}

void
EntityManager::createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    entity_t e = new Entity();
    addComponent<TransformComponent>(e);
    // TODO: other components
    _entities.push_back(e);
    _entsByGroup[grp::WHITEBALL].push_back(e);
    _GS_entities->push_back(e);
}

void
EntityManager::createEffectBall(effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius) {
    entity_t e = new Entity();
    addComponent<TransformComponent>(e);
    // TODO: other components
    _entities.push_back(e);
    _entsByGroup[grp::EFFECTBALLS].push_back(e);
    _GS_entities->push_back(e);
}

void
EntityManager::createTable(/* type */) {
    entity_t e = new Entity();
    // TODO: components
    _entities.push_back(e);
    _entsByGroup[grp::TABLE].push_back(e);
    _GS_entities->push_back(e);
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

void
EntityManager::handleEvents(){
    for (auto* e : _entities)
        e->handleEvents();
}

void
EntityManager::refresh() {

	// remove dead entities from the groups lists, and also those
	// do not belong to the group anymore
	for (ecs::grpId_t gId = 0; gId < ecs::maxGroupId; gId++) {
		auto &groupEntities = _entsByGroup[gId];
		groupEntities.erase(
				std::remove_if(groupEntities.begin(), groupEntities.end(),
						[this](Entity *e) {
							if (isAlive(e)) {
								return false;
							} else {
								delete e;
								return true;
							}
						}), groupEntities.end());
	}

}

} // end of namespace
