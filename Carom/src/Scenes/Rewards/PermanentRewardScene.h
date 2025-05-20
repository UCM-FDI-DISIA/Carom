
#pragma once

#include "RewardScene.h"

class RNG_Manager;

/// @brief Escena que gestiona por si sola todas las recompensas permanentes
class PermanentRewardScene : public RewardScene 
{    
public:
    PermanentRewardScene(Game* game, Reward reward);
    virtual ~PermanentRewardScene();

    void applyReward() override;
    void initObjects() override; 
    void initFunctionalities() override;

    void createRewardTitle();
    void getSkillReward();
    void createRewardText();

private:
    std::string _name;

    RNG_Manager* _rng;
};