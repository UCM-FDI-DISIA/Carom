#pragma once

#include "RewardScene.h"

using body_t = BallInfoDisplayComponent::Body;

class CauldronRewardScene : public RewardScene 
{
    friend class Entity;

    enum Effects{
        ABBACUS,
        BOWLING,
        CRISTAL,
        PETANQUE,
        POKEBALL,
        QUANTIC,
        X2,
        NONE
    };

    Effects _randomEffect;
    int _selectedBallId;

public:
    CauldronRewardScene(Game* game, Reward reward);
    virtual ~CauldronRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override;
};