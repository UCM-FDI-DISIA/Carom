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
    class EndGameScene: public GameScene {
    protected:
       void createTable(); // para que se genere la mesa.
       void createLooseText(); // para q salga el texto de ganar o perdr.
        
    public:
        EndGameScene(Game* g); // para cuando se gana (hay reward).
        virtual ~EndGameScene() = default;

        void setNewState(State* s);
    };

}