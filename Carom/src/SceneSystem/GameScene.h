#ifndef GAME_Scene_H
#define GAME_Scene_H

#include <list>

#include "GameList.h"

// Declaraciones anticipadas
class Entity;
class Game;

/**
 * Estado abstracto del juego.
 *
 * Mantiene una lista de objetos del juego de los que se hace
 * responsable (se encarga de eliminarlos). También mantiene una
 * lista de manejadores de eventos, pero no los elimina.
 */
class GameScene
{
	GameList<Entity> entities;

protected:
	Game* game;

	GameScene(Game* game);

	void addObject(Entity* obj);

public:
	virtual ~GameScene();

    void render() const;
    void update();
    void handleEvent();

	/// Obtiene el juego al que pertenece el estado
	Game* getGame() const;
	/// Elimina los objetos
	void clear();
};

inline Game*
GameScene::getGame() const
{
	return game;
}

#endif // GAME_Scene_H
