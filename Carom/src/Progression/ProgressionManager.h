#pragma once
#include <math.h>
#include <queue>
#include "RNG_Manager.h"
#include <vector>
#include <list>

class CaromScene; // Forward declaration

//Clase que se encarga de gestionar el número de piso y los jefes
class ProgressionManager {
public:
    ProgressionManager() : _bossesList() {}
    ~ProgressionManager() {}

    //Balatro balatrez está jugando balatro         - Diego
    inline void reset() { ante = 0; }
    inline void anteUp() { ante += 1; }
    inline int getAnte() const { return ante; }

    //Aplica una fórmula para calcular la puntuación a batir de una sala en función de una puntuación base dada
    int getScoreToBeat(int baseScore) const;

    //Setea la lista de jefes en un orden aleatorio
    void setBossesList();

    //Devuelve el siguiente jefe de la lista en forma de número, luego es convertido a enum
    int getNextBoss();

private:
    int ante = 0;
    //Vector con los índices de los jefes, se corresponden con sus valores en el enum Boss
    const std::vector<int> _bosses = {0,1};

    //Lista en la que se colocan los jefes de forma desordenda
    std::queue<int> _bossesList = std::queue<int>();
};