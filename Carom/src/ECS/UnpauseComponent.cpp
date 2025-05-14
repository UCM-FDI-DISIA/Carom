#include "UnpauseComponent.h"
#include "GameScene.h"
#include "Entity.h"
#include "Game.h"
#include "InputHandler.h"
#include "ScenesManager.h"
#include "TweenComponent.h"
#include "PhysicsUtils.h"
#include "AudioManager.h"

void UnpauseComponent::handleEvent(){
    if(InputHandler::Instance()->isKeyDown(SDLK_p) && !tween->isTweening()){
        AudioManager::Instance()->playSoundEfect("drawer_close");
        b2Vec2 initialPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer_initial_pos").x, sdlutils().height()/2);
        tween->easePosition(initialPos, .5f, tween::EASE_OUT_ELASTIC, false, [=](){
            _myEntity->getScene().getGame()->getScenesManager()->popScene();
        });
    }
}