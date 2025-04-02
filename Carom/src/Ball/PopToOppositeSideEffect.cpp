#include "PopToOppositeSideEffect.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "WallComponent.h"

using namespace ecs;

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

void 
PopToOppositeSideEffect::onStrikeEnd(){
    _myEntity->removeComponent<PopToOppositeSideEffect>();
}

void 
PopToOppositeSideEffect::popOnCollision(ecs::entity_t other){

    if(!other->tryGetComponent<WallComponent>()) return;// Only if ball collides with table

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
