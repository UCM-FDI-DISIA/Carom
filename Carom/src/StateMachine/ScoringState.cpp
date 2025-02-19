#include "ScoringState.h"

#include "InputHandler.h"

void
ScoringState::onStateEnter() {
    auto& ihdlr = ih();
    // TODO: desactivar input jugador
}

void
ScoringState::onStateExit() {
    // Desapilar estado, apilar estado "resolucion de golpe"
}

bool
ScoringState::checkCondition(State*& state) {
    // comprobar si todas las bolas han dejado de moverse
    return true; // ! placeholder
}