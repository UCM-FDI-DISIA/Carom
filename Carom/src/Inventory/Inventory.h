#pragma once 

#include<array>
#include <vector>

#include "Entity.h"

class StickEffectComponent;

class Texture;
class InventoryManager;

class Inventory {
    const static int MAX_BALLS = 6;
public:
    struct Perma {
        int hitEase, comboEase, caromEase;
        int charisma;   // carisma
        int power;      // poder
        float cunning;  // picardía
    };  
    
    Inventory() : _perma{0, 0, 0, 0, 0,  1.0f}, _balls(), _whiteBall(nullptr), _stick(nullptr) {}
    Inventory(std::vector<entity_t> balls, entity_t whiteball, entity_t stick, Perma perma)
        : _perma(perma), _whiteBall(whiteball), _stick(stick), _balls() 
    {
        std::copy_n(balls.begin(), MAX_BALLS, _balls.begin()); //Esto convierte el vector de bolas en un array
    }

    private:  
    friend InventoryManager;
    
    std::array<entity_t, MAX_BALLS> _balls;
    entity_t _whiteBall;
    entity_t _stick;
    Perma _perma;
};