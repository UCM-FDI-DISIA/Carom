/**
 * Máquina de estados con punteros inteligentes.
 *
 * @file GameSceneMachine.cpp
 * @author Zenith Itadori Llinares
 * @date  Silksong 2025
 */

#include "ScenesManager.h"
#include "RNG_Manager.h"
#include "QuitScene.h"


ScenesManager::ScenesManager()
{
}

ScenesManager::~ScenesManager()
{
	while (!_gameScenes.empty()) {
        _gameScenes.pop();
    }
}

void
ScenesManager::pushScene(std::shared_ptr<GameScene> scene)
{
	scene->init();
	_gameScenes.push(scene);
}

void
ScenesManager::popScene()
{
	// Si el estado final existe y se deja eliminar
	if (!_gameScenes.empty()) {
        _gameScenes.pop();
    }
}

bool
ScenesManager::empty() const
{
	return _gameScenes.empty();
}

ScenesManager::operator bool() const
{
	return !_gameScenes.empty();
}

void
ScenesManager::replaceScene(std::shared_ptr<GameScene> scene)
{
	if (!_gameScenes.empty()) {
		_gameScenes.top() = scene;
	}
}

void
ScenesManager::update()
{
	if (!_gameScenes.empty()) {
		// Esta variable local evita que el estado sea destruido hasta que
		// acabe esta función si su actualización lo desapila de esta pila
		std::shared_ptr<GameScene> current = _gameScenes.top();
		current->update();
	}
 }
 
 void
 ScenesManager::render() const
 {
	 if (!_gameScenes.empty()) {
		// Asumimos que render (const) no desapilará y destruirá el estado
		_gameScenes.top()->render();
	 }
 }
 
 void
 ScenesManager::handleEvent()
 {
	 if (!_gameScenes.empty()) {
		std::shared_ptr<GameScene> current = _gameScenes.top();
		current->handleEvent();
	 }
 }

void
ScenesManager::refresh() {
	if(!_gameScenes.empty()) {
		_gameScenes.top()->refresh();
	}
}
 
void 
ScenesManager::invokeLose()
{
	_gameScenes.top()->getGame()->getProgressionManager()->reset();

	// Main menu es la primera escena
	while (_gameScenes.size() != 1) {
        _gameScenes.pop();
    }


	// Lo mismo que:
	// popScene(); // Poppea endScene
	// CaromScene fue popeada por lose state
	// popScene(); // Poppea reward que esta por debajo
	// popScene(); // Poppea pool scene
	// vuelve a main scene
 }
 
