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
	EntityManager(GameList<Entity> *entities);
	~EntityManager();

	void createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius);

	void createEffectBall(effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius);

	void createTable(/* type */);

	inline std::vector<entity_t>& getEntities() { return _entities; }

	// Setting the state of the entity (alive or dead)
	//
	inline void setAlive(entity_t e, bool alive) {
		e->setAlive(alive);
	}

	// Returns the state of the entity (alive o dead)
	//
	inline bool isAlive(entity_t e){
		return e->isAlive();
	}

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

	// returns the vector of all entities
	//
	inline const auto& getEntities(grpId_t gId) {
		return _entsByGroup[gId];;
	}

	// return true if there is a component with identifier T::id in the entity
	//
	template<typename T>
	inline bool hasComponent(entity_t e) {
		return e->tryGetComponent(cmpId<T>);
	}

	// Returns the component, of the entity, that corresponds to position T,
	// casting it to T*. The casting is done just for ease of use, to avoid casting
	// outside.
	//
	template<typename T>
	inline T* getComponent(entity_t e) {
		return e->getComponent<T>(cmpId<T>);
	}

	// update all entities
	void update();

	// render all entities
	void render();

	// handle events from all entities
	void handleEvents();

	// eliminate dead entities (the implementation of this method
	// is in Manager.cpp, but we could also defined it here).
	//
	void refresh();

private:

	GameList<Entity> *_GS_entities;
	std::vector<entity_t> _entities;
	std::array<std::vector<entity_t>, maxGroupId> _entsByGroup;
};

} // end of namespace
