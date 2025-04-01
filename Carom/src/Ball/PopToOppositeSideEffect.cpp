#include "PopToOppositeSideEffect.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"

using namespace ecs;

void
PopToOppositeSideEffect::init(){
    _mTrans = _myEntity->getTransform();
    _ballHeight = _myEntity->getComponent<RenderTextureComponent>()->getTexture()->height();
    _ballWidth = _myEntity->getComponent<RenderTextureComponent>()->getTexture()->width();

    BallEffect::init();
}

void 
PopToOppositeSideEffect::onStrikeEnd(){
    _myEntity->removeComponent<PopToOppositeSideEffect>();
}

void 
PopToOppositeSideEffect::popOnCollision(ecs::entity_t other){
    if(other->getID() != ecs::grp::grpId::TABLE) return; // Only if ball collides with table

    b2Vec2 a_collPos = other->getTransform()->getPosition();

    if(a_collPos.x > *&sdlutils().svgs().at("game").at("top_cushion_coll").x){
        _mTrans->setPosition({(float)*&sdlutils().svgs().at("game").at("left_cushion_coll").x + _ballWidth, _mTrans->getPosition().y});
    }
    else if(a_collPos.x < *&sdlutils().svgs().at("game").at("top_cushion_coll").x){
        _mTrans->setPosition({(float)*&sdlutils().svgs().at("game").at("right_cushion_coll").x - _ballWidth, _mTrans->getPosition().y});
    }

    if(a_collPos.y > *&sdlutils().svgs().at("game").at("left_cushion_coll").y){
        _mTrans->setPosition({_mTrans->getPosition().x, (float)*&sdlutils().svgs().at("game").at("top_cushion_coll").y + _ballHeight});
    }
    else if(a_collPos.y < *&sdlutils().svgs().at("game").at("left_cushion_coll").y){
        _mTrans->setPosition({_mTrans->getPosition().x, (float)*&sdlutils().svgs().at("game").at("bottom_cushion_coll").y - _ballHeight});
    }
}
