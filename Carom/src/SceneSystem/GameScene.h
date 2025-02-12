#ifndef GAME_Scene_H
#define GAME_Scene_H

#include <list>

#include "GameList.h"

class Game;

// Declaraciones anticipadas
namespace ecs{
	class Entity;

	/**
 * Estado abstracto del juego.
 *
 * Mantiene una lista de objetos del juego de los que se hace
 * responsable (se encarga de eliminarlos). También mantiene una
 * lista de manejadores de eventos, pero no los elimina.
 */
class GameScene
{
	GameList<ecs::Entity> entities;

protected:
	Game* game;

	GameScene(Game* game);

	void addObject(ecs::Entity* obj);

public:
	virtual ~GameScene();

    virtual void render();
    virtual void update();
    virtual void handleEvent();

	/// Obtiene el juego al que pertenece el estado
	Game* getGame() const;
	/// Elimina los objetos
	virtual void clear();
};

inline Game*
GameScene::getGame() const
{
	return game;
}

}




#endif // GAME_Scene_H
