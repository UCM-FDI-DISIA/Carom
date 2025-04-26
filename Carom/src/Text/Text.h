#pragma once

#include <string>

#include "SDL.h"

struct Text {
    std::string text;
    std::string font;
    SDL_Color color;
};