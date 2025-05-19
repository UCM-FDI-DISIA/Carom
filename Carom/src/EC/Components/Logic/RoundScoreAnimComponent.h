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

    /// @brief Constructor de RoundScoreAnimComponent
    /// @param ent El round score
    /// @param scoreToMedium la puntuacion necesaria para que pase de pequeño a mediano
    /// @param scoreToMax la puntuacion necesaria para que pase de mediano a grande
    RoundScoreAnimComponent(entity_t ent, int scoreToMedium, int scoreToMax);
    ~RoundScoreAnimComponent() {}


    /// @brief Añade a la entidad los componentes necesarios y los guarda
    void init() override;
    /// @brief comprueba si tiene que cambiar y lo hace si es asi. Si la puntuacion es 0 se reinicia.
    void update() override;
    inline void setRoundScore(int score) {_score = score;}
    inline void resetScore() {_isMid = false; _isMax = false;}
};