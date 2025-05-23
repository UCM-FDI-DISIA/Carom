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

class RNG_Manager;
/**
 * Máquina de estados del juego.
 *
 * Se comporta como una pila y proporciona métodos update, render y
 * handleEvent para aplicarlos sobre el estado actual.
 */
class ScenesManager
{
	// Pila (como las de EDA) de punteros inteligentes a estados del juego
	std::stack<std::shared_ptr<GameScene>> _gameScenes;

public:
	ScenesManager();
	~ScenesManager();

	PoolScene* getPoolScene();

	// Apila un nuevo estado, que se convierte en el estado actual,
	// manteniendo el anterior en la pila. Llama al init() de la escena apilada
	void pushScene(std::shared_ptr<GameScene> scene);
	// Reemplaza el estado actual por el nuevo estado
	void replaceScene(std::shared_ptr<GameScene> scene);
	// Desapila el estado actual y pasa al siguiente en la pila
	// (no hace nada si no la pila es vacía)
	void popScene();
	inline std::shared_ptr<GameScene> top() { return _gameScenes.top(); }

	bool empty() const;
	operator bool() const;

	// Métodos que delegan en los métodos homónimos de GameScene
	// sobre el estado actual (no hacen nada si la pila es vacía)
	void update();
	void render() const;
	void handleEvent();

	void refresh();

	//Método que gestina la pila al PERDER
	void invokeLose();
};

#endif // GAME_STATE_MACHINE_H
