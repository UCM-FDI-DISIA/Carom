#pragma once

#include <string>

#include "SDL.h"

/// @brief Estructura sencilla para facilitar la creación de texturas de texto
struct Text {
    std::string text;
    std::string font;
    SDL_Color color;
};