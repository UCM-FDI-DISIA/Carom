#include "PauseScene.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"

#include "TweenComponent.h"
#include "PhysicsUtils.h"
#include "InventoryManager.h"

#include <iostream>

#include "Button.h"
#include "AudioManager.h"


PauseScene::PauseScene(Game* g, GameScene* scene): UIScene(g) {
    _bottomScene = scene;

    previousTheme = AudioManager::Instance()->getCurrentTheme();
    // instantiateInventory();
}

PauseScene::~PauseScene(){
    AudioManager::Instance()->setVolumeMusicTrack(PAUSE_THEME, 0);
    AudioManager::Instance()->setVolumeMusicTrack(trackName(previousTheme), 64);
}

void
PauseScene::initObjects() {
    AudioManager::Instance()->changeToPauseTheme();

    UIScene::instantiateInventory();
}


void PauseScene::render(){
    _bottomScene->render();
    GameScene::render();
}

