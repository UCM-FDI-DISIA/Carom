#pragma once
#include "Component.h"
#include <string>
#include <functional>
#include <queue>

class TextDisplayComponent;

class DialogueTextComponent : public Component{

    class DialogueContainer{
        int _lastTime;
        const int MILISECONDS_BETWEEN_CHARS = 60;
        std::string _textToPrint;
        int _index =0;
    
        std::function<void()> _callbackOnEnd;
    public:
        DialogueContainer(std::string textToPrint, std::function<void()> callbackOnEnd = [](){});
    
        void update(TextDisplayComponent* textDisplay);
        std::string getTextToPrint(){return _textToPrint;}
        void playCallback(){_callbackOnEnd();}
    };

    std::queue<DialogueContainer> _dialogues;
    TextDisplayComponent* _textDisplay;
    bool _canSkip;
public:
    __CMPID_DECL__(cmp::DIALOGUE);
    inline DialogueTextComponent(entity_t e,TextDisplayComponent* textDisplay, bool canSkip = true): Component(e),_textDisplay(textDisplay), _canSkip(canSkip){}

    void update() override;
    void init() override;

    inline void render() override{}

    void handleEvent() override;

    void addDialogue(std::string textToPrint, std::function<void()> callbackOnEnd = [](){});
};

