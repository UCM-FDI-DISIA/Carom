#pragma once
#include "EndScene.h"

class ScenesManager;
class EndGameScene: public EndScene {  
public:
    EndGameScene(Game* g); // para cuando se gana (hay reward).
    virtual ~EndGameScene() = default;
};
