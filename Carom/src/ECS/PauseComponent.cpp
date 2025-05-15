#include "PauseComponent.h"
#include "HandleEventComponent.h"
#include "GameScene.h"
#include "Entity.h"
#include "Game.h"
#include "InputHandler.h"
#include "ScenesManager.h"
#include "PauseScene.h"

#include "AudioManager.h"
#include <memory>

void PauseComponent::handleEvent(){
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)){
        AudioManager::Instance()->playSoundEfect("drawer_open");
        auto game = _myEntity->getScene().getGame();
        game->getScenesManager()->pushScene(std::make_shared<PauseScene>(game, &_myEntity->getScene()));
    }
}