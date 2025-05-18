#pragma once

#include "InstantRewardScene.h"
#include "BallInfoDisplayComponent.h"
#include "PoolScene.h"

/// @brief Recompensa que le da un efecto aleatorio a una bola elegida
class CauldronRewardScene : public InstantRewardScene
{
    friend class Entity;
    BallId _randomEffect;

public:
    CauldronRewardScene(Game* game, Reward reward);
    virtual ~CauldronRewardScene();

    virtual void applyReward() override;
    virtual void initObjects() override; 
    virtual void atRender() override;
};