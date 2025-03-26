#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "RNG_Manager.h"

class ScenesManager;
class RNG_Manager;

class TextDisplayComponent;
class EndScene: public GameScene {
protected:
    void createTable(); // para que se genere la mesa.
    void createText(std::string text);       // para q salga el texto de ganar o perdr.
    void createExitButton(); // crea el boton de cambio de escena.
    
public:
    EndScene(Game* g) : GameScene(g){} // para cuando se gana (hay reward).
    virtual ~EndScene() = default;

    void setNewState(State* s);
};
