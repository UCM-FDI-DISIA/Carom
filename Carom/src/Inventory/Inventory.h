#pragma once 

#include<array>
#include <vector>

class StickEffetComponent;
class Entity;
class InventoryManager;

class Inventory {
    public:
    struct Perma {
        int hitEase, comboEase, caromEase;
        int charisma;
        int power;
        float cunning; 
    };  
    
    private:  
    friend InventoryManager;
    const static int MAX_BALLS = 6;
    
    std::array<Entity*, MAX_BALLS> _balls;
    StickEffetComponent* _stick;
    Perma _perma;
};