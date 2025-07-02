#pragma once
#include "BallHandler.h"
#include "ecs.h"
#include <string>

class CaromScene;

class BallEffect
{
protected:
    std::string _name;
    std::string _description;
    BallHandler* _handler;
public:
    BallEffect(BallHandler* hdlr): _handler(hdlr) {}
    ~BallEffect(){}

    virtual void onHit(entity_t ent) {};
    virtual void onStrikeEnd() {};
    virtual void onBeingTargeted() {};
    virtual void onMultChanged() {};

    virtual void init(){}
    virtual void update() {}
    virtual effectId_t getEffectId() = 0;

    //Método que devuelve a partir del id de componente el nombre del efecto
    //Se puede usar para obtener la textura
    static std::string effectTextureName(BallEffect* effect)
    {
        switch(effect->getEffectId())
        {
            case effect::BOWLING: return "BowlingEffect";
            case effect::PETANQUE: return "PetanqueEffect";
            case effect::POKEBALL: return "PokeballEffect";
            case effect::CRYSTAL: return "CristalEffect";
            case effect::ABBACUS: return "AbacusEffect";
            case effect::QUANTIC: return "QuanticEffect";
            case effect::X2: return "X2Effect";
        }

        return "";
    }
};