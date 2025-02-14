#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cassert>

#include <SDLUtils.h>

#include "ecs.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Entity.h"

namespace ecs {

/*
 * A class for managing the list of entities, groups, etc.
 */
class EntityManager {

public:
	EntityManager();
	virtual ~EntityManager();

	// Adds empty entity and returns its position in _entities vector
	int addEntity();

	// Add a game entity of objId
	// Returns the position in the _entities array
	int addEntity(obj::objId objId);

	inline std::vector<entity_t>& getEntities() { return _entities; }

	// Setting the state of the entity (alive or dead)
	//
	inline void setAlive(int id, bool alive) {
		entity_t e = getEntities()[id];
		e->setAlive(alive);
	}

	// Returns the state of the entity (alive o dead)
	//
	inline bool isAlive(int id) {
		entity_t e = getEntities()[id];
		return e->isAlive();
	}

	template<typename T, typename ...Ts>
	inline void addComponent(int id, Ts &&... args){
		addComponent<T>(_entities[id], std::forward<Ts>(args)...);
	}

	template<typename T>
	inline bool removeComponent(int id) {
		return removeComponent(_entities[id]);
	}

	// update all entities
	void update();

	// render all entities
	void render();

private:
	// TODO groups
	// for now:
	std::vector<entity_t> _entities;

	// Entity counting
	int _id;

	// Adds a component to an entity. It receives the type T (to be created),
	// and the list of arguments (if any) to be passed to the constructor.
	//
	template<typename T, typename ...Ts>
	inline void addComponent(entity_t e, Ts &&... args) {
		// the component id
		static_assert(cmpId<T> < ecs::maxComponentId);

		// create, initialise and install the new component
		T *c = new T(e, std::forward<Ts>(args)...);

		if (!e->addComponent<T>(c)) {
			delete c;
		}
	}

	// Removes the component T, if any, from the entity.
	template<typename T>
	inline bool removeComponent(entity_t e) {
		return e->removeComponent<T>();
	}

	// Returns the component, of the entity, that corresponds to position T,
	// casting it to T*. The casting is done just for ease of use, to avoid casting
	// outside.
	//
	template<typename T>
	inline T* getComponent(entity_t e) {
		return e->getComponent<T>(cmpId<T>);
	}

	// return true if there is a component with identifier T::id in the entity
	//
	template<typename T>
	inline bool hasComponent(entity_t e) {
		return e->tryGetComponent(cmpId<T>);
	}
};

} // end of namespace
