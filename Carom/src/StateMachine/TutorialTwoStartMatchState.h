#pragma once

#include "StartMatchState.h"

// Forward declarations
class CaromScene;

class TutorialTwoStartMatchState: public StartMatchState {
protected:
    bool _finished = true; // TODO: por defecto a false, se pone a true cuando termina la animación ->finish()
public:
    TutorialTwoStartMatchState(CaromScene* scene);
    bool checkCondition(State*& state) override;
};
