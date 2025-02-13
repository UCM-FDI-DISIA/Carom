// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <cassert>

#include "../external/sdlutils/include/SDLUtils.h"

#include "ecs.h"
#include "Component.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Entity.h"

namespace ecs {

/*
 * A class for managing the list of entities, groups, etc.
 */
// ! BÁSICO
class Manager {

public:
	Manager();
	virtual ~Manager();

	// Add a game entity
	//
	inline void addEntity(obj::objId objId) {

		switch (objId){
			case (obj::WHITEBALL): {
				entity_t e = new Entity();
				addComponent<TransformComponent>(e);
				addComponent<RenderTextureComponent>(e, &sdlutils().images().at("tennis_ball"));
				entities.push_back(std::move(e));
				break;
			}
			// TODO
		}
	}

	// Setting the state of the entity (alive or dead)
	//
	inline void setAlive(entity_t e, bool alive) {
		e->setAlive(alive);
	}

	// Returns the state of the entity (alive o dead)
	//
	inline bool isAlive(entity_t e) {
		return e->isAlive();
	}

	// Adds a component to an entity. It receives the type T (to be created),
	// and the list of arguments (if any) to be passed to the constructor.
	//
	template<typename T, typename ...Ts>
	inline void addComponent(entity_t e, Ts &&... args) {
		// the component id
		static_assert(cmpId<T> < ecs::maxComponentId);

		// delete the current component, if any
		//TODO necesario?
		// removeComponent<T>(e);

		// create, initialise and install the new component
		//
		Component *c = new T(e, std::forward<Ts>(args)...);
		c->setContext(e);
		// c->initComponent(); // TODO
		e->_components[cmpId<T>] = c;
		e->_currentComponents.push_back(c);

		// // return it to the user so i can be initialised if needed
		// return static_cast<T*>(c);
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

	// update all entities
	void update(); // TODO

	// render all entities
	void render(); // TODO


private:
	// TODO groups
	// for now:
	std::vector<entity_t> entities;
};

} // end of namespace
