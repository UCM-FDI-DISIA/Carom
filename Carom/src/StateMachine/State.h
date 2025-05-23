#pragma once

class CaromScene;

//Interfaz de State, que es usada por una máquina de estados para cambiar de estado
class State{
public:
    inline State(CaromScene* scene) : _scene(scene) {}

    //checkea la condicion
    //Si no ha encontrado ninguna condicion valida, devuelve false
    //Si ha encontrado una condicion valida, devuelve true y el estado al que va
    virtual bool checkCondition(State*& state)=0;

    //se ejecuta cuando se entra al estado
    virtual void onStateEnter()=0;
    //se ejecuta cuando se sale del estado
    virtual void onStateExit()=0;

    virtual void finish() {};

    void setBallInputActive(bool active);
    void setAimLineActive(bool active);
    void setStickActive(bool active);

protected:
    CaromScene* _scene;
};