#pragma once
#include "HelperScene.h"

class TextHelperScene: public HelperScene{
public:
    TextHelperScene(Game* g, GameScene* bottom, std::string textToShow);
};
