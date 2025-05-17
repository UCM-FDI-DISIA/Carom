#include "DialogueTextComponent.h"
#include "TextDisplayComponent.h"
#include "Entity.h"
#include "SDLUtils.h"

#include "InputHandler.h"
#include "AudioManager.h"

void DialogueTextComponent::init(){
}

void DialogueTextComponent::update(){
    if(_dialogues.size() > 0)
    _dialogues.front().update(_textDisplay);
}

void DialogueTextComponent::handleEvent(){
    if(!_canSkip) return;
    
    auto input = InputHandler::Instance();
    if((input->mouseButtonDownEvent() && input->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT))){
        if(_dialogues.size() > 0){
            //si el texto que se muestra es distinto al que debe aparecer, lo completa
            if(_dialogues.front().getTextToPrint() != _textDisplay->getDisplayedText()){
                _textDisplay->setDisplayedText(_dialogues.front().getTextToPrint());
            }
            else{
                //si no, pasas al sifuiente
                _dialogues.front().playCallback();
                _dialogues.pop();

                _textDisplay->setDisplayedText(" ");
            }
        }
    }
}

void DialogueTextComponent::addDialogue(std::string textToPrint, std::function<void()> callbackOnEnd){
    _dialogues.emplace(DialogueContainer(textToPrint, callbackOnEnd));
}

void DialogueTextComponent::DialogueContainer::update(TextDisplayComponent* _textDisplay){
    if(_textDisplay->getDisplayedText() != _textToPrint && _lastTime + MILISECONDS_BETWEEN_CHARS <= sdlutils().currRealTime()){
        _lastTime = sdlutils().currRealTime();
        
        std::string displayedText = _textToPrint;
        displayedText.resize(_index+1);
        _index++;
        
        //REPRODUCIR SONIDO CORRESPONDIENTE
        char charToPlay = displayedText[displayedText.size()-1];
        if(charToPlay == 'ñ') charToPlay = 'n';
        else if(charToPlay == 'á') charToPlay = 'a';
        else if(charToPlay == 'é') charToPlay = 'e';
        else if(charToPlay == 'í') charToPlay = 'i';
        else if (charToPlay == 'ó') charToPlay = 'o';

        if(displayedText.size() > 0 && charToPlay >= 'a' && charToPlay<='z'){
            
            std::string lol = "sound_";
            lol.push_back(charToPlay);
            AudioManager::Instance()->playSoundEfect(lol);
            // sdlutils().soundEffects().at(lol).play();
        }

        _textDisplay->setDisplayedText(displayedText);
    }
}

DialogueTextComponent::DialogueContainer::DialogueContainer(std::string textToPrint, std::function<void()> callbackOnEnd ):
    _textToPrint(textToPrint), _callbackOnEnd(callbackOnEnd), _lastTime(0)
    {
}