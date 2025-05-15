#include "RoundScoreAnimComponent.h"
#include "RenderSpritesheetComponent.h"
#include "AnimatorComponent.h"
#include <exception>
#include "Entity.h"
#include "SDLUtils.h"

/// @brief Constructor de RoundScoreAnimComponent
/// @param ent El round score
/// @param scoreToMedium la puntuacion necesaria para que pase de pequeño a mediano
/// @param scoreToMax la puntuacion necesaria para que pase de mediano a grande
RoundScoreAnimComponent::RoundScoreAnimComponent(entity_t ent,  int scoreToMedium, int scoreToMax ):
LogicComponent(ent), _score(0), _scoreToMedium(scoreToMedium), _scoreToMax(scoreToMax), _isMid(false), _isMax(false){}

/// @brief Añade a la entidad los componentes necesarios y los guarda
void
RoundScoreAnimComponent::init() {
    _myRender = _myEntity->getComponent<RenderTextureComponent>();

    Animation* anim = &sdlutils().animations().at("score_from_1_to_2");
    _myEntity->addComponent<RenderSpritesheetComponent>(
        new RenderSpritesheetComponent(_myEntity, anim->_spriteSheet, renderLayer::SCORE_CONTAINER,
        anim->_scale, anim->_spriteRows, anim->_spriteCols, anim->_frameList[0].frame));

    _myEntity->addComponent<AnimatorComponent>(new AnimatorComponent(_myEntity, anim));

    _mySheetRender = _myEntity->getComponent<RenderSpritesheetComponent>();
    _myAnimator = _myEntity->getComponent<AnimatorComponent>();
    _myAnimator->setEnabled(false);
    _mySheetRender->setEnabled(false);
    
}

// Este es con diferencia el método más feo que he hecho en el proyecto porque me da una pereza hacerlo bien
/// @brief comprueba si tiene que cambiar y lo hace si es asi. Si la puntuacion es 0 se reinicia.
void
RoundScoreAnimComponent::update(){

    if (!_isMid && _score >= _scoreToMedium){

        _myRender->setEnabled(false);
        _mySheetRender->setEnabled(true);
        Animation* anim = &sdlutils().animations().at("score_from_1_to_2");
        _myAnimator->setAnimation(anim);
        _myAnimator->setEnabled(true);
        _isMid = true;
    }
    
    if(!_isMax && _score >= _scoreToMax){
        if(_myAnimator->isEnabled()) return;

        _myRender->setEnabled(false);
        _mySheetRender->setEnabled(true);
        Animation* anim = &sdlutils().animations().at("score_from_2_to_3");
        _myAnimator->setAnimation(anim);
        _myAnimator->setEnabled(true);
        _isMax = true;
    }

    if(!_myRender->isEnabled() && !_myAnimator->isEnabled()){

        _mySheetRender->setEnabled(false);
        _myRender->setEnabled(true);

        if(_isMid) _myRender->setTexture(&sdlutils().images().at("roundScorerColt"));
        if(_isMax) _myRender->setTexture(&sdlutils().images().at("roundScorerMax"));
    }

    if(_isMid && _score <= 0){
        _isMid = false;
        _isMax = false;
        _myRender->setTexture(&sdlutils().images().at("roundScorerPup"));
    }
}