/**
 * Máquina de estados con punteros inteligentes.
 *
 * @file GameSceneMachine.h
 * @author Rubén Rubio
 * @date TPV1 2024
 */

#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <memory>
#include <stack>

#include "GameScene.h"
#include <SDL.h>

/**
 * Máquina de estados del juego.
 *
 * Se comporta como una pila y proporciona métodos update, render y
 * handleEvent para aplicarlos sobre el estado actual.
 */
class ScenesManager
{
	// Pila (como las de EDA) de punteros inteligentes a estados del juego
	std::stack<std::shared_ptr<GameScene>> GameScenes;

public:
	~ScenesManager();

	// Apila un nuevo estado, que se convierte en el estado actual,
	// manteniendo el anterior en la pila
	void pushState(std::shared_ptr<GameScene> state);
	// Reemplaza el estado actual por el nuevo estado
	void replaceState(std::shared_ptr<GameScene> state);
	// Desapila el estado actual y pasa al siguiente en la pila
	// (no hace nada si no la pila es vacía)
	void popState();

	// Sobrecargas que reciben un puntero normal
	void pushState(GameScene* state);
	void replaceState(GameScene* state);

	bool empty() const;
	operator bool() const;

	// Métodos que delegan en los métodos homónimos de GameScene
	// sobre el estado actual (no hacen nada si la pila es vacía)
	void update();
	void render() const;
	void handleEvent();
};

inline void
ScenesManager::pushState(GameScene* state)
{
	pushState(std::shared_ptr<GameScene>(state));
}

inline void
ScenesManager::replaceState(GameScene* state)
{
	replaceState(std::shared_ptr<GameScene>(state));
}

#endif // GAME_STATE_MACHINE_H
