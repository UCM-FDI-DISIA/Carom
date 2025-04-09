#pragma once

#include <SDLUtils.h>
#include <list>
#include <vector>
#include <array>
#include <unordered_map>
#include <box2d/box2d.h>

#include "GameList.h"
#include "ecs.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "Frame.h"
#include "CameraComponent.h"

class Game;

class TweenComponent;

// Declaraciones anticipadas

/**
 * Estado abstracto del juego.
 *
 * Mantiene una lista de objetos del juego de los que se hace
 * responsable (se encarga de eliminarlos). También mantiene una
 * lista de manejadores de eventos, pero no los elimina.
 */
class GameScene
{
private:
    std::vector<entity_t> _entsRenderable;

protected:
    GameList<Entity> _entities;
    std::array<std::vector<entity_t>, maxGroupId> _entsByGroup;

    Game* game;
    CameraComponent* _camera = nullptr;

	GameScene(Game* game);
	GameScene();

	
	// Este metodo permite un comportamiento de la escena al instanciarla
	//
	inline virtual void init(){}

    // Deletes all entities
    void clearEntities();

    // Create entities that represent and compose the table. The table as a whole is a group.
    void createTable();
    //creates a background
    void createBackground(std::string key);

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
    inline T* addComponent(entity_t e, Ts &&... args) {
        // the component id exists
        static_assert(cmpId<T> < maxComponentId);

        // create component
        T *c = new T(e, std::forward<Ts>(args)...);

        // install the new component if entity doesn't have one of the type
        if (!e->addComponent<T>(c)) {
            delete c;
				return nullptr;
        }
		return c;
    }

    // Removes the component T, if any, from the entity.
    // Returns true if succeded, false if didn't existed.
    //
    template<typename T>
    inline bool removeComponent(entity_t e) {
        return e->removeComponent<T>();
    }

    //creates pause entity with PauseComponent
    void createPauseEntity();

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

    inline GameList<Entity>& getEntities() { 
        return _entities;
    }

    // Returns the vector of all entities of a group ID.
    //
    inline auto& getEntitiesOfGroup(grpId_t gId) {
        return _entsByGroup[gId];
    }

    inline const auto& getRenderEntities(){
        return _entsRenderable;
    }

    inline void eraseRenderEntity(entity_t e){
        auto itR = find(_entsRenderable.begin(), _entsRenderable.end(), e);
        _entsRenderable.erase(itR);
    }

    inline void pushToRenderEntities(entity_t e) { 
        _entsRenderable.push_back(e);
        sortRenderOrder();
    }

    // Enables all entity's components
    //
    inline void enableEntity(entity_t e) {
        e->activate();
    }

    // Disables all entity's components
    //
    inline void disableEntity(entity_t e) {
        e->deactivate();
    }

public:
    virtual ~GameScene();

    virtual void render();
    virtual void update();
    virtual void handleEvent();
    virtual void refresh();

    /// Obtiene el juego al que pertenece el estado
    Game* getGame() const;
    CameraComponent* getCamera();
    //Must have CameraComponent attached
    void setCamera(Entity* e);
    /// Elimina los objetos
    virtual void clear();
    // Set rendering order. Called by render texture component on init.
    void sortRenderOrder();

protected:

    virtual void updatePhysics() {};
    virtual void updateScene() {};

#ifdef _DEBUG
protected:
    bool _canFastForwardPhysics = false;
public:
    virtual void setCanFastForward(bool active) {};
#endif
};

inline Game*
GameScene::getGame() const
{
    return game;
}
