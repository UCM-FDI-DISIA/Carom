#pragma once

#include <vector>

class Texture;
struct Frame;

/// @brief Animación de una spritesheet, todas las animaciones son cargadas mediante sdlutils y son definidas
///        en resources.json
struct Animation {
    
    Texture* _spriteSheet = nullptr;
    /// @brief Columnas y filas del sprite, creo que queda claro
    int _spriteRows, _spriteCols;
    /// @brief Multiplicador sobre el tamaño original del frame para ajustar el tamaño de render
    float _scale;

    /// @brief Frames que componen la animación, el orden de índices (de menor a mayor) indica el orden de reproducción
    std::vector<Frame> _frameList;

    /// @brief Tipos de animaciones (como finalizan)
    enum AnimationType {
        /// @brief Reinicia la animacioón al primer frame
        LOOP,
        /// @brief Elimina la entidad
        KILLMYSELF,
        /// @brief Desactiva el componente de animacion
        TURNOFF,
        /// @brief Elimina el componente de animación
        DESTROYANIM
    };

    /// @brief Que pasa cuando la animación termina el último frame
    AnimationType _animType;
};