#pragma once
#include "BallEffect.h"
class BallHandler;

class AbacusEffect : public ecs::BallEffect
{
private:
    int _bonusPoints = 1;

public:
    AbacusEffect(ecs::entity_t ent) : ecs::BallEffect(ent) {
        _name = "Ábaco";
        _description = "Suma al ser golpeada" + _bonusPoints;
    }
    ~AbacusEffect() {}

    void init() override;
    void onHit(ecs::entity_t ent) override;
    __CMPID_DECL__(ecs::cmp::ABACUS_EFFECT);
};