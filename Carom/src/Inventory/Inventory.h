#pragma once 

#include<array>
#include <vector>

class StickEffectComponent;
class Entity;
class Texture;
class InventoryManager;

class Inventory {
        const static int MAX_BALLS = 6;
    public:
    struct Perma {
        int hitEase, comboEase, caromEase;
        int charisma;
        int power;
        float cunning; 
    };  

    struct StickProps {
        StickEffectComponent* effect;
        Texture* texture;
    };
    
    Inventory() : _perma{0, 0, 0, 0, 0,  1.0f}, _balls(), _stick {nullptr, nullptr} {}
    Inventory(std::vector<Entity*> balls, StickProps stickEffect, Perma perma)
        : _perma(perma), _stick(stickEffect), _balls() 
    {
        std::copy_n(balls.begin(), MAX_BALLS, _balls.begin());
    }

    private:  
    friend InventoryManager;
    
    std::array<Entity*, MAX_BALLS> _balls;
    StickProps _stick;
    Perma _perma;
};