#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include <functional>

struct Animation;

/// @brief Representa un sprite de una animacion
struct Frame {
    /// @brief Tiempo en (1000/60) milisegundos que el fotograma está activo
    int activeTime;
    int col;
    int row;
    /// @brief Escala del frame con respecto a la escala de la animación
    float scale = 1.0;

    /// @brief Callbacks a ejecutar al activar y desactivar el frame
    std::function<void()> enterCallback = {};
    std::function<void()> exitCallback = {};
};