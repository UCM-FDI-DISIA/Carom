#pragma once

#include <vector>

class Texture;
struct Frame;

/// @brief Animación de una spritesheet
struct Animation {
    
    Texture* _spriteSheet = nullptr;
    int _spriteRows, _spriteCols;
    float _scale;

    std::vector<Frame> _frameList;

    enum AnimationType {
        LOOP,
        KILLMYSELF,
        TURNOFF,
        DESTROYANIM
    };

    AnimationType _animType;
};