#pragma once

#include <string>
#include <vector>

#include "RenderTextureComponent.h"


class RewardInfoDisplayComponent : public RenderTextureComponent {
    std::string _titleText;
    std::string _titleFont;

    std::vector<std::string> _rewardText;
    std::vector<std::string> _descriptionText;
    std::string _bodyFont;

    SDL_Color _color;
    
    void reGenerateTexture();

public:
    /// @brief Constructor del componente para mostrar las recompensas en la mesa de Pool
    /// @param entity La entidad a la que pertenece
    /// @param scale la escala del rect donde se crea el texto
    /// @param titleText El texto de título que renderiza
    /// @param rewardText El nombre de las recompensas
    /// @param descText Breve descripción de cada recompensa
    /// @param color El color del texto a mostrar
    /// @param titleFont La key con la que buscar la fuente en el resources.json
    /// @param bodyFont La key con la que buscar la fuente en el resources.json
    RewardInfoDisplayComponent(Entity* entity, layerId_t renderLayer, float scale, 
        std::string titleText, std::vector<std::string> rewardText, std::vector<std::string> descText,
        SDL_Color color, std::string titleFont, std::string bodyFont);

    void changeFont(std::string key);
    void setColor(SDL_Color);
    void setTitleText(std::string text);
};


