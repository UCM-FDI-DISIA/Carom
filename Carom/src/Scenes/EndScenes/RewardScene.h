#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"

class ScenesManager;
class RNG_Manager;

namespace ecs{
    class TextDisplayComponent;
    class RewardScene: public GameScene {
    protected:
        // quiza sea bueno hacer una clase padre intermedia para metodos que se repitan en RewardScene y EndGameScene.
       void createTable(); // para que se genere la mesa.
       void createWinText(); // para q salga el texto de ganar o perdr.
       void createExitButton(); // crea el boton de cambio de escena.
        
    public:
        RewardScene(Game* g); // para cuando se gana (hay reward).
        virtual ~RewardScene() = default;

        void setNewState(State* s);
    };

}