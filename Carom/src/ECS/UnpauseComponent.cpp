#include "UnpauseComponent.h"
#include "GameScene.h"
#include "Entity.h"
#include "Game.h"
#include "InputHandler.h"
#include "ScenesManager.h"

void UnpauseComponent::handleEvent(){
    if(InputHandler::Instance()->isKeyDown(SDLK_p)){
        _myEntity->getScene().getGame()->getScenesManager()->popScene();
    }
}