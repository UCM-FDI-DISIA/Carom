#pragma once
#include "GameScene.h"
#include "State.h"

class MainScene: public ecs::GameScene {
protected:
//el estado en el que se encuentra la escena actualmente
    State* _currentState = nullptr;
public:
    MainScene(State* s, Game* g);
    ~MainScene();

    //Cambiar el estado actual por uno nuevo. Flujo sería:
    //- Llama a onStateExit() del estado a cambiar
    //- Cambia el estado por el nuevo
    //- Llama a onStateEnter() del nuevo estado
    void setNewState(State* s);
    //Reproduce:
    //- update() del estado actual (si tuviera algun comportamiento especifico)
    //- update() de todas las entidades de la escena
    void update() override;
    //devuelve el estado en el que se encuentra la escena principal
    State* getCurrentState();
};