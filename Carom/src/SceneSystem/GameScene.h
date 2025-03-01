#pragma once

#include <SDLUtils.h>
#include <list>
#include <vector>
#include <array>
#include <box2d/box2d.h>
#include "GameList.h"
#include "ecs.h"
#include "Entity.h"
#include "Camera.h"

class Game;

// Declaraciones anticipadas
namespace ecs{

		/**
	 * Estado abstracto del juego.
	 *
	 * Mantiene una lista de objetos del juego de los que se hace
	 * responsable (se encarga de eliminarlos). También mantiene una
	 * lista de manejadores de eventos, pero no los elimina.
	 */
	class GameScene
	{
	protected:
		GameList<Entity> _entities;
		std::array<std::vector<entity_t>, maxGroupId> _entsByGroup;
		std::vector<entity_t> _entsRenderable;

		Game* game;
		Camera _worldCamera;
		Camera _UICamera;

	GameScene(Game* game);
	GameScene();

	
	// Este metodo permite un comportamiento de la escena al instanciarla
	//
	inline virtual void init(){}

		// Create entities that represent and compose the table. The table as a whole is a group.
		void createTable();
		//creates a background
		void createBackground(std::string key);

		inline GameList<Entity>& getEntities() { return _entities; }

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
		// NOTE: If the entity already has this component no component is added!
		//
		template<typename T, typename ...Ts>
		inline void addComponent(entity_t e, Ts &&... args) {
			// the component id exists
			static_assert(cmpId<T> < ecs::maxComponentId);

			// create component
			T *c = new T(e, std::forward<Ts>(args)...);

			// install the new component if entity doesn't have one of the type
			if (!e->addComponent<T>(c)) {
				delete c;
			}
		}

		// Removes the component T, if any, from the entity.
		// Returns true if succeded, false if didn't existed.
		//
		template<typename T>
		inline bool removeComponent(entity_t e) {
			return e->removeComponent<T>();
		}

	public:
		// Return true if there is a component with identifier T::id in the entity.
		//
		template<typename T>
		inline bool hasComponent(entity_t e) {
			return e->tryGetComponent();
		}

		// Returns pointer to the component <T> of the entity.
		//
		template<typename T>
		inline T* getComponent(entity_t e) {
			return e->getComponent<T>();
		}

		// Returns the vector of all entities of a group ID.
		//
		inline auto& getEntitiesOfGroup(grpId_t gId) {
			return _entsByGroup[gId];
		}

		// Enables all entity's components
		//
		inline void enableEntity(entity_t e) {
			e->enable();
		}

		// Disables all entity's components
		//
		inline void disableEntity(entity_t e) {
			e->disable();
		}

	public:


		virtual ~GameScene();

		virtual void render();
		virtual void update();
		virtual void handleEvent();

		/// Obtiene el juego al que pertenece el estado
		Game* getGame() const;
		Camera* getWorldCamera();
		Camera* getUICamera();
		void setWorldCamera(b2Vec2 pos);
		void setUICamera(b2Vec2 pos);
		/// Elimina los objetos
		virtual void clear();
		// Set rendering order. Called by render texture component on init.
		void sortRenderOrder();
	};

	inline Game*
	GameScene::getGame() const
	{
		return game;
	}

}
