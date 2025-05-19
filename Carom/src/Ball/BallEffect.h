#pragma once
#include "Component.h"
#include "BallHandler.h"
#include "ecs.h"
#include <string>

class CaromScene;

class BallEffect : public Component
{
protected:
    std::string _name;
    std::string _description;
    BallHandler* _handler;
public:
    BallEffect(entity_t ent) : Component(ent) {}
    ~BallEffect();

    virtual void init() override;

    virtual void onHit(entity_t ent) {};
    virtual void onStrikeEnd() {};
    virtual void onBeingTargeted() {};
    virtual void onMultChanged() {};

    void render() override {}
    void handleEvent() override {}
    virtual void update() override {}
    virtual cmpId_t getEffectId() = 0;

    //Método que devuelve a partir del id de componente el nombre del efecto
    //Se puede usar para obtener la textura
    static std::string effectTextureName(BallEffect* effect)
    {
        switch(effect->getEffectId())
        {
            case cmp::BOWLING_EFFECT: return "BowlingEffect";
            case cmp::PETANQUE_EFFECT: return "PetanqueEffect";
            case cmp::POKEBALL_EFFECT: return "PokeballEffect";
            case cmp::CRISTAL_EFFECT: return "CristalEffect";
            case cmp::ABACUS_EFFECT: return "AbacusEffect";
            case cmp::QUANTIC_EFFECT: return "QuanticEffect";
            case cmp::X2_EFFECT: return "X2Effect";
        }

        return "";
    }
};