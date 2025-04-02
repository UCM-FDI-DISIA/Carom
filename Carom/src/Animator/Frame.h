#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include <functional>

struct Animation;

/// @brief Representa un sprite de una animacion
struct Frame {
    /// @brief Tiempo en (1000/60) milisegundos que el fotograma está activo
    const int activeTime;
    int frame;

    inline Uint32 getActiveMiliseconds() { return activeTime * (1000/60); }
};