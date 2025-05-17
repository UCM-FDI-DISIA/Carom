#pragma once

#include "InstantRewardScene.h"

class StickRewardScene : public InstantRewardScene 
{    
public:
    StickRewardScene(Game* game, Reward reward);
    virtual ~StickRewardScene();

    void atRender() override;

    virtual void applyReward() override;
    virtual void initObjects() override; 
private:
    StickId _stickReward;

    Texture* idToTexture(StickId);

    bool _invSelected = false;
    bool _newSelected = false;

    RenderTextureComponent* _newStickTextureComponent = nullptr;
    RenderTextureComponent* _oldStickTextureComponent = nullptr;
};