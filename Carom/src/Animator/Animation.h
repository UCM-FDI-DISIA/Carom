#pragma once

#include <vector>

class Texture;
struct Frame;

/// @brief Animación de una spritesheet
struct Animation {
    
    Texture* spriteSheet = nullptr;
    int spriteRows, spriteCols;
    
    std::vector<Frame> frameList;

    enum AnimationType {
        LOOP,
        DELETE,
        TURN_OFF
    };
};