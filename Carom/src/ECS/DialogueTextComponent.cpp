#include "DialogueTextComponent.h"
#include "TextDisplayComponent.h"
#include "Entity.h"
#include "SDLUtils.h"

void DialogueTextComponent::init(){
}

void DialogueTextComponent::update(){
    if(_textDisplay->getDisplayedText() != _textToPrint && _lastTime + MILISECONDS_BETWEEN_CHARS >= sdlutils().currTime()){
        _lastTime = sdlutils().currTime();

        std::string displayedText = _textDisplay->getDisplayedText();
        char charToAdd = _textToPrint[displayedText.size()];

        displayedText += charToAdd;
        //REPRODUCIR SONIDO CORRESPONDIENTE

        _textDisplay->setDisplayedText(displayedText);
    }
}