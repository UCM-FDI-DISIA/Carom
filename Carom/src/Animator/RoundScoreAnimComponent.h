#pragma once
#include "LogicComponent.h"
#include "RenderTextureComponent.h"
#include <vector>
class RenderSpritesheetComponent;
class AnimatorComponent;

class RoundScoreAnimComponent : public LogicComponent {
    RenderTextureComponent* _myRender;
    RenderSpritesheetComponent* _mySheetRender;
    AnimatorComponent* _myAnimator;

    int _score;
    int _scoreToMedium;
    int _scoreToMax;

    bool _isMid;
    bool _isMax;
public:
    __CMPID_DECL__(cmp::ROUND_SCORE_ANIMATOR);

    RoundScoreAnimComponent(entity_t ent, int scoreToMedium, int scoreToMax);
    ~RoundScoreAnimComponent() {}

    void init() override;
    void update() override;
    inline void setRoundScore(int score) {_score = score;}
    inline void resetScore() {_isMid = false; _isMax = false;}
};