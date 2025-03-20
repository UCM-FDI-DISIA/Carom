#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"

class ScenesManager;
class RNG_Manager;

namespace ecs{
    class EndGameScene: public GameScene {
    protected:
       void createTable(); // para que se genere la mesa.
        
    public:
        EndGameScene(Game* g); // para cuando se gana (hay reward).
        virtual ~EndGameScene() = default;

        void setNewState(State* s);
    };

}