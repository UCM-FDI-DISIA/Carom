#pragma once
#include "BallEffect.h"
class BallHandler;

class AbacusEffect : public BallEffect
{
private:
    int _bonusPoints = 1;

public:
    AbacusEffect(entity_t ent) : BallEffect(ent) {
        _name = "Ábaco";
        _description = "Suma al ser golpeada" + _bonusPoints;
    }
    ~AbacusEffect() {}

    void init() override;
    void onHit(entity_t ent) override;
    __CMPID_DECL__(cmp::ABACUS_EFFECT);

    cmpId_t getEffectId() override {return cmp::ABACUS_EFFECT;};
};