/**
 * Máquina de estados con punteros inteligentes.
 *
 * @file GameSceneMachine.cpp
 * @author Rubén Rubio
 * @date TPV1 2024
 */

#include "ScenesManager.h"

using namespace std;

ScenesManager::~ScenesManager()
{
	while (!GameScenes.empty())
		GameScenes.pop();
}

void
ScenesManager::pushState(shared_ptr<GameScene> state)
{
	GameScenes.push(std::move(state));
}

void
ScenesManager::popState()
{
	// Si el estado final existe y se deja eliminar
	if (!GameScenes.empty())
		GameScenes.pop();
}

bool
ScenesManager::empty() const
{
	return GameScenes.empty();
}

ScenesManager::operator bool() const
{
	return !GameScenes.empty();
}

void
ScenesManager::replaceState(shared_ptr<GameScene> state)
{
	if (!GameScenes.empty())
		GameScenes.top() = std::move(state);
}

void
ScenesManager::update()
{
	if (!GameScenes.empty()) {
		// Esta variable local evita que el estado sea destruido hasta que
		// acabe esta función si su actualización lo desapila de esta pila
		shared_ptr<GameScene> current = GameScenes.top();
		current->update();
	}
}

void
ScenesManager::render() const
{
	if (!GameScenes.empty()) {
		// Asumimos que render (const) no desapilará y destruirá el estado
		GameScenes.top()->render();
	}
}

void
ScenesManager::handleEvent()
{
	if (!GameScenes.empty()) {
		shared_ptr<GameScene> current = GameScenes.top();
		current->handleEvent();
	}
}
