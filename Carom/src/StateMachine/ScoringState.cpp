#include "ScoringState.h"

#include "PostScoringState.h"
#include "EntityManager.h"
#include "CaromScene.h"


void
ScoringState::onStateEnter() {
    // TODO: desactivar palo (input, render)
}

void
ScoringState::onStateExit() {
    _scene->setNewState(new PostScoringState(_scene));
}

// bool
// ScoringState::checkCondition(State*& state) {
//     // comprobar si todas las bolas han dejado de moverse
// }
