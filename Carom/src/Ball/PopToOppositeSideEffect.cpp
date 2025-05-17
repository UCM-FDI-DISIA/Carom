#include "PopToOppositeSideEffect.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "WallComponent.h"
#include "EventOnCollision.h"
#include "AudioManager.h"

/// @brief Registra las posiciones de las paredes para compararlas al chocar con algo y asegurarse de que es una pared
void
PopToOppositeSideEffect::init(){
    _mTrans = _myEntity->getTransform();

    _leftPos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("left_cushion_coll").x,
        *&sdlutils().svgs().at("game").at("left_cushion_coll").y
    );

    _rightPos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("right_cushion_coll").x,
        *&sdlutils().svgs().at("game").at("right_cushion_coll").y
    );

    _topPos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("top_cushion_coll").x,
        *&sdlutils().svgs().at("game").at("top_cushion_coll").y
    );

    _botPos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("bottom_cushion_coll").x,
        *&sdlutils().svgs().at("game").at("bottom_cushion_coll").y
    );

    BallEffect::init();
}

/// @brief Al acabar el golpe se eliminan los efectos hasta el siguiente golpe
void 
PopToOppositeSideEffect::onStrikeEnd(){
    _myEntity->removeComponent<EventOnCollision>();
    _myEntity->removeComponent<PopToOppositeSideEffect>();

}

/// @brief Al chocar comprueba si ha chocado con una pared. Si lo ha hecho mira que pared ha sido y se teletransporta a la pared opuesta
/// @param other La pared con la que se choca
void 
PopToOppositeSideEffect::popOnCollision(entity_t other){

    if(!other->tryGetComponent<WallComponent>()) return;// Only if ball collides with table
    AudioManager::Instance()->playSoundEfect("pop_opposite", 80);

    b2Vec2 a_collPos = other->getTransform()->getPosition();
    
    if(a_collPos.x > _topPos.x){
        _mTrans->setPosition({_leftPos.x + 0.3f, _mTrans->getPosition().y});
    }
    else if(a_collPos.x < _topPos.x){
        _mTrans->setPosition({_rightPos.x - 0.3f, _mTrans->getPosition().y});
    }

    if(a_collPos.y > _leftPos.y){
        _mTrans->setPosition({_mTrans->getPosition().x, _botPos.y + 0.3f});
    }
    else if(a_collPos.y < _leftPos.y){
        _mTrans->setPosition({_mTrans->getPosition().x, _topPos.y - 0.3f});
    }
}
