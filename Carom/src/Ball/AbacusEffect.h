#pragma once
#include "BallEffect.h"
class BallHandler;

class AbacusEffect : public BallEffect
{
private:
    int _bonusPoints = 1;
    BallHandler* _handler;

public:
    AbacusEffect(ecs::entity_t ent) : BallEffect(ent) {
        _name = "Ábaco";
        _description = "Suma al ser golpeada" + _bonusPoints;
    }
    ~AbacusEffect() {}

    void init() override;
    void onHit(ecs::entity_t ent) override;
    __CMPID_DECL__(ecs::cmp::ABACUS_EFFECT);
};