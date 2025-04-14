/**
 * Máquina de estados con punteros inteligentes.
 *
 * @file GameSceneMachine.cpp
 * @author Zenith Itadori Llinares
 * @date  Silksong 2025
 */

 #include "ScenesManager.h"
 #include "RNG_Manager.h"


using namespace std;

ScenesManager::ScenesManager()
{
}

ScenesManager::~ScenesManager()
{
	while (!GameScenes.empty()) {
        delete GameScenes.top();
        GameScenes.pop();
    }
}

void
ScenesManager::pushScene(GameScene* scene)
{
	scene->init();
	GameScenes.push(scene);
}

void
ScenesManager::popScene()
{
	// Si el estado final existe y se deja eliminar
	if (!GameScenes.empty()) {
        delete GameScenes.top();
        GameScenes.pop();
    }
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
ScenesManager::replaceScene(GameScene* scene)
{
	if (!GameScenes.empty()) {
		GameScene* current = GameScenes.top();
		GameScenes.top() = scene;
		delete current;
	}
}

void
ScenesManager::update()
{
	if (!GameScenes.empty()) {
		// Esta variable local evita que el estado sea destruido hasta que
		// acabe esta función si su actualización lo desapila de esta pila
		GameScene* current = GameScenes.top();
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
		GameScene* current = GameScenes.top();
		current->handleEvent();
	 }
 }

void
ScenesManager::refresh() {
	if(!GameScenes.empty()) {
		GameScenes.top()->refresh();
	}
}
 
 void 
 ScenesManager::invokeLose(){
	 //TODO
 }
 
