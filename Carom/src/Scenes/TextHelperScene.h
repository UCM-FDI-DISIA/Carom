#pragma once
#include "HelperScene.h"

class TextHelperScene: public HelperScene{
public:
    TextHelperScene(Game* g, std::shared_ptr<GameScene> bottom, std::string textToShow);
};
