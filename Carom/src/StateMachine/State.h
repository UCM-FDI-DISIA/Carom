#pragma once

//Interfaz de State, que es usada por una maquina de estados para cambiar de estado
class State{
public:

//update en caso de que se quiera hacer algo en especifico en el estado
virtual void update() =0;

//checkea la condicion
//Si no ha encontrado ninguna condicion valida, devuelve false
//Si ha encontrado una condicion valida, devuelve true y el estado al que va
virtual bool checkCondition(State& state)=0;

//se ejecuta cuando se entra al estado
virtual void onStateEnter() =0;
//se ejecuta cuando se sale del estado
virtual void onStateExit() =0;
};