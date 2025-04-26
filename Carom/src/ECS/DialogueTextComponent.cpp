#include "DialogueTextComponent.h"
#include "TextDisplayComponent.h"
#include "Entity.h"
#include "SDLUtils.h"

void DialogueTextComponent::init(){
}

void DialogueTextComponent::update(){
    if(_textDisplay->getDisplayedText() != _textToPrint && _lastTime + MILISECONDS_BETWEEN_CHARS <= sdlutils().currRealTime()){
        _lastTime = sdlutils().currRealTime();
        
        std::string displayedText = _textToPrint;
        displayedText.resize(_index+1);
        _index++;
        
        //REPRODUCIR SONIDO CORRESPONDIENTE

        _textDisplay->setDisplayedText(displayedText);
    }
}