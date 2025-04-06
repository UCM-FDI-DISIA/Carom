#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include <functional>

struct Animation;

/// @brief Representa un sprite de una animacion
struct Frame {

    int frame;

    /// @brief Tiempo en (1000/60) milisegundos (1/60 segundos) que el fotograma está activo
    /// Esto solo vale para añadir los datos de forma mas accesible, para obtener el tiempo real
    /// se debe utilizar getActiveMiliseconds()
    const int activeTime;

    inline Uint32 getActiveMiliseconds() { return activeTime * (1000/60); }
};