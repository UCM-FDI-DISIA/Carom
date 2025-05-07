#include "RoundScoreAnimComponent.h"
#include "RenderSpritesheetComponent.h"
#include "AnimatorComponent.h"
#include <exception>
#include "Entity.h"
#include "SDLUtils.h"

RoundScoreAnimComponent::RoundScoreAnimComponent(entity_t ent,  int scoreToMedium, int scoreToMax ):
LogicComponent(ent), _score(0), _scoreToMedium(scoreToMedium), _scoreToMax(scoreToMax), _isMid(false), _isMax(false){}

void
RoundScoreAnimComponent::init() {
    _myRender = _myEntity->getComponent<RenderTextureComponent>();
}

void
RoundScoreAnimComponent::update(){

    if (!_isMid && _score >= _scoreToMedium){
        _myRender->setEnabled(false);
        Animation* anim = &sdlutils().animations().at("score_from_1_to_2");
        _myEntity->addComponent<RenderSpritesheetComponent>(
            new RenderSpritesheetComponent(_myEntity, anim->_spriteSheet, renderLayer::SCORE_CONTAINER,
            anim->_scale, anim->_spriteRows, anim->_spriteCols, anim->_frameList[0].frame));
        
        _myEntity->addComponent<AnimatorComponent>(new AnimatorComponent(_myEntity, anim));
        _isMid = true;
    }
    
    if(!_isMax && _score >= _scoreToMax){
        if(_myEntity->getComponent<RenderSpritesheetComponent>()) return;

        _myRender->setEnabled(false);
        Animation* anim = &sdlutils().animations().at("score_from_2_to_3");
        _myEntity->addComponent<RenderSpritesheetComponent>(
            new RenderSpritesheetComponent(_myEntity, anim->_spriteSheet, renderLayer::SCORE_CONTAINER,
            anim->_scale, anim->_spriteRows, anim->_spriteCols, anim->_frameList[0].frame));
        
        _myEntity->addComponent<AnimatorComponent>(new AnimatorComponent(_myEntity, anim));
        _isMax = true;
    }

    if(!_myRender->isEnabled() && !_myEntity->getComponent<RenderSpritesheetComponent>()){

        _myRender->setEnabled(true);   

        if(_isMid) _myRender->setTexture(&sdlutils().images().at("roundScorerColt"));
        if(_isMax) _myRender->setTexture(&sdlutils().images().at("roundScorerMax"));
    }
}