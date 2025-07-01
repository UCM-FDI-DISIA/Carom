#pragma once
#include "BallEffect.h"
class BallHandler;

class AbacusEffect : public BallEffect
{
private:
    int _bonusPoints = 1;

public:
    AbacusEffect(BallHandler* hndlr) : BallEffect(hndlr) {
        _name = "Ábaco";
        _description = "Suma al ser golpeada" + _bonusPoints;
    }
    ~AbacusEffect() {}
    
    void onHit(entity_t ent) override;

    __EFFID_DECL__(effect::ABBACUS);

    effectId_t getEffectId() override {return effect::ABBACUS;}
};