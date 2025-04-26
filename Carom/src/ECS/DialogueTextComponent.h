#pragma once
#include "LogicComponent.h"
#include <string>

class TextDisplayComponent;
class DialogueTextComponent : public LogicComponent{
    std::string _textToPrint;
    const int MILISECONDS_BETWEEN_CHARS = 200;

    int _lastTime;

    int _index =0;
    TextDisplayComponent* _textDisplay;
public:
    __CMPID_DECL__(cmp::DIALOGUE);
    inline DialogueTextComponent(entity_t e,TextDisplayComponent* textDisplay ,std::string text): LogicComponent(e),_textDisplay(textDisplay), _textToPrint(text), _lastTime(0){}

    void update() override;
    void init() override;
};