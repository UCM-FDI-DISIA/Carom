
#pragma once

#include "RewardScene.h"

/// @brief Escena que gestiona por si sola todas las recompensas permanentes
class PermanentRewardScene : public RewardScene 
{    
public:
    PermanentRewardScene(Game* game, Reward reward);
    virtual ~PermanentRewardScene();

    void applyReward() override;
    void initObjects() override; 
    void initFunctionalities() override;

private:
    std::string _name;
};