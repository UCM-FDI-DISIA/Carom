#include "PauseComponent.h"
#include "HandleEventComponent.h"
#include "GameScene.h"
#include "Entity.h"
#include "Game.h"
#include "InputHandler.h"
#include "ScenesManager.h"
#include "PauseScene.h"

void PauseComponent::handleEvent(){
    if(InputHandler::Instance()->isKeyDown(SDLK_p)){
        auto game = _myEntity->getScene().getGame();
        game->getScenesManager()->pushScene(new PauseScene(game, &_myEntity->getScene()));
    }
}