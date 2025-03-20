#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"

class ScenesManager;
class RNG_Manager;

namespace ecs{
    class RewardScene: public GameScene {
    protected:
        // quiza sea bueno hacer una clase padre intermedia para metodos que se repitan en RewardScene y EndGameScene.
       void createTable(); // para que se genere la mesa.
        
    public:
        RewardScene(Game* g); // para cuando se gana (hay reward).
        virtual ~RewardScene() = default;

        void setNewState(State* s);
    };

}