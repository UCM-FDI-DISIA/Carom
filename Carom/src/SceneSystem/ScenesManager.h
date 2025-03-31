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
	std::stack<std::shared_ptr<ecs::GameScene>> GameScenes;

public:
	~ScenesManager();

	// Apila un nuevo estado, que se convierte en el estado actual,
	// manteniendo el anterior en la pila
	void pushScene(std::shared_ptr<ecs::GameScene> scene);
	// Reemplaza el estado actual por el nuevo estado
	void replaceScene(std::shared_ptr<ecs::GameScene> scene);
	// Desapila el estado actual y pasa al siguiente en la pila
	// (no hace nada si no la pila es vacía)
	void popScene();

	// Sobrecargas que reciben un puntero normal
	void pushScene(ecs::GameScene* scene);
	void replaceScene(ecs::GameScene* scene);

	bool empty() const;
	operator bool() const;

	// Métodos que delegan en los métodos homónimos de GameScene
	// sobre el estado actual (no hacen nada si la pila es vacía)
	void update();
	void render() const;
	void handleEvent();
	void refresh();

	//Método que crea la escena de derrota, se puede llamar en cualquier momento
	void invokeLose(Game* g);
};

inline void
ScenesManager::pushScene(ecs::GameScene* scene)
{
	pushScene(std::shared_ptr<ecs::GameScene>(scene));
}

inline void
ScenesManager::replaceScene(ecs::GameScene* scene)
{
	replaceScene(std::shared_ptr<ecs::GameScene>(scene));
}

#endif // GAME_STATE_MACHINE_H
